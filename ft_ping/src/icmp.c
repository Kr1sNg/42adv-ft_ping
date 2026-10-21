/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:44:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/21 12:11:46 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ICMP package layout
// Type: 8 (1 byte) - Code: 0 (1 byte) - Checksum (2 bytes = short) - Identifier
// (2 bytes) - Sequence (2 bytes) - Payload (optional data bytes)

#include "../includes/ft_ping.h"

int create_icmp_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd == -1)
    {
        if (errno == EPERM || errno == EACCES)
        {
            fprintf(stderr, "ft_ping: permission denied creating raw socket\n");
            fprintf(stderr, "ft_ping: try running with sudo or CAP_NET_RAW\n");
        }
        else
        {
            fprintf(stderr, "ft_ping: socket: %s\n", strerror(errno));
        }
        return (-1);
    }
    return (sockfd);
}

// An Internet checksum works on 2 bytes (16-bit) words:
// 1. Combine each pair of bytes into a 16-bit value.
// 2. Add the values together
// 3. Fold any overflow back into the lower 16 bits.
// 4. Invert all bits.

unsigned short calculate_checksum(const unsigned char *data, size_t length)
{
    unsigned int sum = 0;
    size_t i = 0;

    while (i + 1 < length)
    {
        sum += ((unsigned int)data[i] << 8) | (unsigned int)data[i + 1];
        i += 2;
    }

    if (i < length)
    {
        sum += (unsigned int)data[i] << 8;
    }

    while (sum >> 16)
    {
        sum = (sum & 0xffffU) + (sum >> 16);
    }
    return (unsigned short)(~sum & 0xffffU);
}

int send_echo_req(int sockfd, struct sockaddr_in *dest,
                  unsigned short identifier, unsigned short sequence)
{
    struct
    {
        struct icmphdr header;
        unsigned char payload[32];
    } packet;
    size_t packet_size;
    ssize_t bytes_sent;

    memset(&packet, 0, sizeof(packet));
    packet_size = sizeof(packet.header) + sizeof(packet.payload);

    packet.header.type = ICMP_ECHO;
    packet.header.code = 0;
    packet.header.un.echo.id = htons(identifier);
    packet.header.un.echo.sequence = htons(sequence);

    memset(packet.payload, 'A', sizeof(packet.payload));

    packet.header.checksum = 0;
    packet.header.checksum =
        htons(calculate_checksum((const unsigned char *)&packet, packet_size));

    bytes_sent = sendto(sockfd, &packet, packet_size, 0,
                        (struct sockaddr *)dest, sizeof(*dest));
    if (bytes_sent == -1)
    {
        fprintf(stderr, "ft_ping: sendto: %s\n", strerror(errno));
        return (-1);
    }
    if ((size_t)bytes_sent != packet_size)
    {
        fprintf(stderr, "ft_ping: incomplete ICMP packet sent\n");
        return (-1);
    }
    printf("ft_ping: sent %zu bytes of ICMP data\n", packet_size);
    return (0);
}

int recv_echo_reply(int sockfd, unsigned short identifier,
                    unsigned short sequence, char *src_ip, size_t src_ip_size,
                    size_t *reply_size)
{
    unsigned char buffer[1500];
    struct sockaddr_in sender;
    socklen_t sender_length;
    ssize_t bytes_received;
    struct iphdr ip_header;
    struct icmphdr icmp_header;
    size_t ip_header_size;
    size_t icmp_offset;

    while (1)
    {
        memset(&sender, 0, sizeof(sender));
        sender_length = sizeof(sender);

        bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                  (struct sockaddr *)&sender, &sender_length);
        if (bytes_received == -1)
        {
            if (errno == EINTR)
                continue;
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                return (1);
            fprintf(stderr, "ft_ping: recvfrom: %s\n", strerror(errno));
            return (-1);
        }

        if ((size_t)bytes_received < sizeof(struct iphdr))
            continue;

        memcpy(&ip_header, buffer, sizeof(ip_header));

        if (ip_header.version != 4)
            continue;
        ip_header_size = (size_t)ip_header.ihl * 4;
        if (ip_header_size < sizeof(struct iphdr))
            continue;

        if ((size_t)bytes_received < ip_header_size + sizeof(struct icmphdr))
            continue;

        icmp_offset = ip_header_size;
        memcpy(&icmp_header, buffer + icmp_offset, sizeof(icmp_header));

        if (ip_header.protocol != IPPROTO_ICMP)
            continue;

        if (icmp_header.type != ICMP_ECHO || icmp_header.code != 0)
            continue;

        if (ntohs(icmp_header.un.echo.id) != identifier)
            continue;

        if (ntohs(icmp_header.un.echo.sequence) != sequence)
            continue;

        if (inet_ntop(AF_INET, &sender.sin_addr, src_ip, src_ip_size) == NULL)
        {
            fprintf(stderr, "ft_ping: inet_ntop: %s\n", strerror(errno));
            return (-1);
        }

        *reply_size = (size_t)bytes_received - ip_header_size;
        return (0);
    }
}