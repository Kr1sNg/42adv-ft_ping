/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/20 11:44:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 15:14:48 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// ICMP package layout
// Type: 8 (1 byte) - Code: 0 (1 byte) - Checksum (2 bytes = short) - Identifier
// (2 bytes) - Sequence (2 bytes) - Payload (optional data bytes)

#include "../includes/ft_ping.h"

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

void fill_payload(unsigned char *payload)
{
    struct timespec now;
    size_t i;

    i = 0;
    while (i < PING_PAYLOAD_SIZE)
    {
        payload[i] = (unsigned char)i;
        i++;
    }
    clock_gettime(CLOCK_MONOTONIC, &now);
    memcpy(payload, &now, sizeof(now));
}

int send_echo_request(int sockfd, const struct sockaddr_in *destination,
                      uint16_t identifier, uint16_t sequence)
{
    unsigned char packet[sizeof(struct icmphdr) + PING_PAYLOAD_SIZE];
    struct icmphdr *header;
    ssize_t sent_bytes;

    header = (struct icmphdr *)packet;
    memset(header, 0, sizeof(*header));
    header->type = ICMP_ECHO;
    header->code = 0;
    header->un.echo.id = htons(identifier);
    header->un.echo.sequence = htons(sequence);
    fill_payload(packet + sizeof(*header));
    header->checksum = 0;
    header->checksum = htons(calculate_checksum(packet, sizeof(packet)));
    sent_bytes =
        sendto(sockfd, packet, sizeof(packet), 0,
               (const struct sockaddr *)destination, sizeof(*destination));
    if (sent_bytes == -1)
    {
        fprintf(stderr, "ft_ping: sending packet: %s\n", strerror(errno));
        return -1;
    }
    if ((size_t)sent_bytes != sizeof(packet))
    {
        fprintf(stderr, "ft_ping: incomplete ICMP packet sent\n");
        return -1;
    }
    return 0;
}