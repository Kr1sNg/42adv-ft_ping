/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:44:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/22 18:04:48 by tat-nguy         ###   ########.fr       */
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

uint16_t calculate_checksum(const void *data, size_t length)
{
    const uint8_t *bytes = data;
    uint32_t sum = 0;
    size_t i = 0;

    while (i + 1 < length)
    {
        sum += ((uint32_t)bytes[i] << 8) | bytes[i + 1];
        i += 2;
    }

    if (i < length)
        sum += (uint32_t)bytes[i] << 8;

    while (sum >> 16)
        sum = (sum & 0xffffU) + (sum >> 16);

    return (uint16_t)(~sum & 0xffffU);
}

// uint16_t calculate_checksum(const uint8_t *data, size_t len)
// {
// 	uint16_t sum = 0;
// 	while (len -= sizeof(short))
// 		sum += *data++;
// 	return (~sum);
// }

int send_echo_req(int sockfd, struct sockaddr_in *dest, uint16_t identifier,
                  uint16_t sequence)
{
    struct s_icmp_packet
    {
        struct icmphdr header;
        uint8_t payload[PING_PAYLOAD_SIZE];
    } packet;
    size_t i = 0;
    ssize_t bytes_sent;

    memset(&packet, 0, sizeof(packet));
    packet.header.type = ICMP_ECHO;
    packet.header.code = 0;
    packet.header.un.echo.id = htons(identifier);
    packet.header.un.echo.sequence = htons(sequence);

    while (i < sizeof(packet.payload))
    {
        packet.payload[i] = 'A';
        i++;
    }

    packet.header.checksum = 0;
    packet.header.checksum =
        htons(calculate_checksum((const uint8_t *)&packet, sizeof(packet)));

    bytes_sent = sendto(sockfd, &packet, sizeof(packet), 0,
                        (struct sockaddr *)dest, sizeof(*dest));
    if (bytes_sent == -1)
    {
        fprintf(stderr, "ft_ping: sendto: %s\n", strerror(errno));
        return (-1);
    }
    if ((size_t)bytes_sent != sizeof(packet))
    {
        fprintf(stderr, "ft_ping: incomplete ICMP packet sent\n");
        return (-1);
    }
    return (0);
}

int recv_echo_reply(const t_recv_config *config, t_ping_reply *reply)
{
    uint8_t buffer[1500];
    struct sockaddr_in sender;
    socklen_t sender_length;
    struct timespec deadline;
    size_t received_size;
    size_t header_size;
    size_t total_length;
    ssize_t bytes_received;

    if (make_deadline(config->timeout_ms, &deadline) == -1) // TODO
        return -1;
    while (!g_stop)
    {
        result = wait_for_packet(config->sockfd, &deadline); // TODO
        if (result != 1)
            return result == 0 ? 1 : result;

        memset(&sender, 0, sizeof(sender));
        sender_length = sizeof(sender);
        bytes_received = recvfrom(config->sockfd, buffer, sizeof(buffer), 0,
                                  (struct sockaddr *)&sender, &sender_length);
        if (bytes_received == -1)
        {
            if (errno == EINTR)
                continue;
            fprintf(stderr, "ft_ping: recvfrom: %s\n", strerror(errno));
            return (-1);
        }
        received_size = (size_t)bytes_received;
        if (validate_ip_header(buffer, received_size, &header_size,
                               &total_length, config->verbose) != 0)
            continue;
        if (validate_icmp_reply)
    }

    deadline.tv_sec += (time_t)(timeout_ms / 1000);
    deadline.tv_nsec += (long)(timeout_ms % 1000) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L)
    {
        deadline.tv_sec++;
        deadline.tv_nsec -= 1000000000L;
    }

    while (!g_stop_requested)
    {
        wait_result = deadline_remaining(&deadline, &timeout);
        if (wait_result == -1)
            return -1;
        if (wait_result == 0)
            return 1;

        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        wait_result = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
        if (wait_result == -1)
        {
            if (errno == EINTR)
                continue;
            perror("ft_ping: select");
            return -1;
        }
        if (wait_result == 0)
            continue;

        memset(&sender, 0, sizeof(sender));
        sender_length = sizeof(sender);
        bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0,
                                  (struct sockaddr *)&sender, &sender_length);
        if (bytes_received == -1)
        {
            if (errno == EINTR)
                continue;
            perror("ft_ping: recvfrom");
            return -1;
        }

        /* Validate that a complete IPv4 header is present. */
        if ((size_t)bytes_received < sizeof(struct iphdr))
        {
            report_ignored_packet(verbose, "truncated IPv4 header");
            continue;
        }
        memcpy(&ip_header, buffer, sizeof(ip_header));
        if (ip_header.version != 4)
        {
            report_ignored_packet(verbose, "not an IPv4 packet");
            continue;
        }
        ip_header_size = (size_t)ip_header.ihl * 4;
        if (ip_header_size < sizeof(struct iphdr) ||
            ip_header_size > (size_t)bytes_received)
        {
            report_ignored_packet(verbose, "invalid IPv4 header length");
            continue;
        }
        if (ip_header.protocol != IPPROTO_ICMP)
        {
            report_ignored_packet(verbose, "not an ICMP packet");
            continue;
        }

        /*
         * IPv4 total length includes the IPv4 header and its payload.
         * Do not parse beyond either the declared length or the
         * bytes actually received.
         */
        total_length = (size_t)ntohs(ip_header.tot_len);
        if (total_length < ip_header_size + sizeof(struct icmphdr))
        {
            report_ignored_packet(verbose, "invalid IPv4 total length");
            continue;
        }
        if (total_length > (size_t)bytes_received)
        {
            report_ignored_packet(verbose, "truncated IPv4 packet");
            continue;
        }

        icmp_length = total_length - ip_header_size;
        memcpy(&icmp_header, buffer + ip_header_size, sizeof(icmp_header));

        if (icmp_header.type != ICMP_ECHOREPLY || icmp_header.code != 0)
        {
            report_ignored_packet(verbose, "not an ICMP Echo Reply");
            continue;
        }

        /* A valid ICMP message has a zero result when checksummed
         * together with its checksum field. */
        if (calculate_checksum(buffer + ip_header_size, icmp_length) != 0)
        {
            report_ignored_packet(verbose, "invalid ICMP checksum");
            continue;
        }

        if (ntohs(icmp_header.un.echo.id) != identifier ||
            ntohs(icmp_header.un.echo.sequence) != sequence)
        {
            report_ignored_packet(verbose,
                                  "identifier or sequence number mismatch");
            continue;
        }

        if (inet_ntop(AF_INET, &sender.sin_addr, source_ip, source_ip_size) ==
            NULL)
        {
            perror("ft_ping: inet_ntop");
            return -1;
        }
        *ttl = ip_header.ttl;
        *reply_size = icmp_length;
        return 0;
    }
    return 2;
}