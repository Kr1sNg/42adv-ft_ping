/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:50 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:05:27 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

// Payload: the send time first (the reply echoes it back, which gives the
// RTT even for a late reply), then filler bytes.
static void fill_payload(unsigned char *payload)
{
    struct timespec now;
    size_t i = 0;

    while (i < PING_PAYLOAD_SIZE)
    {
        payload[i] = (unsigned char)i;
        i++;
    }
    clock_gettime(CLOCK_MONOTONIC, &now);
    memcpy(payload, &now, sizeof(now));
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

// ICMP Echo Request layout (8-byte header + data):
// Type: 8 (1 byte) | Code: 0 (1 byte) | Checksum (2 bytes)
// Identifier (2 bytes) | Sequence (2 bytes) | Payload (56 bytes)
static int send_echo_request(int sockfd, const struct sockaddr_in *dest,
                             uint16_t identifier, uint16_t sequence)
{
    unsigned char packet[sizeof(struct icmphdr) + PING_PAYLOAD_SIZE];
    struct icmphdr *header = (struct icmphdr *)packet;

    memset(header, 0, sizeof(*header));
    header->type = ICMP_ECHO;
    header->code = 0;
    header->un.echo.id = htons(identifier);
    header->un.echo.sequence = htons(sequence);
    fill_payload(packet + sizeof(*header));
    header->checksum = 0;
    header->checksum = htons(calculate_checksum(packet, sizeof(packet)));

    if (sendto(sockfd, packet, sizeof(packet), 0, (const struct sockaddr *)dest,
               sizeof(*dest)) == -1)
    {
        fprintf(stderr, "ft_ping: sending packet: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

// Count an Echo Reply; returns true if its sequence was already seen (DUP!)
static bool record_reply(t_ping_stats *stats, const t_ping_reply *reply)
{
    if (stats->seen[reply->sequence])
    {
        stats->duplicates++;
        return (true);
    }
    stats->seen[reply->sequence] = true;
    stats->received++;
    if (stats->received == 1 || reply->rtt_ms < stats->min_rtt)
        stats->min_rtt = reply->rtt_ms;
    if (stats->received == 1 || reply->rtt_ms > stats->max_rtt)
        stats->max_rtt = reply->rtt_ms;
    stats->totat_rtt += reply->rtt_ms;
    stats->total_rtt_squared += reply->rtt_ms * reply->rtt_ms;
    return (false);
}

// Send one Echo Request per second until Ctrl-C. Between two sends, handle
// every packet that arrives (even a late reply), then print the statistics.
int run_loop(const t_ping_context *context)
{
    t_ping_stats stats = {0};
    t_ping_reply reply = {0};
    uint16_t identifier = (uint16_t)(getpid() & 0xffff);
    uint16_t sequence = 0;
    double next_send_ms = now_ms();
    int result;

    print_header(context, identifier);
    while (!g_stop)
    {
        if (now_ms() >= next_send_ms)
        {
            if (send_echo_request(context->sockfd, &context->dest, identifier,
                                  sequence) == -1)
                return (1);
            stats.seen[sequence] = false;
            sequence++;
            stats.transmitted++;
            next_send_ms += PING_INTERVAL_MS;
        }

        result =
            recv_echo_reply(context->sockfd, identifier, next_send_ms, &reply);
        if (result == -1)
            return 1;
        if (result == 1 && reply.is_error)
            print_error(context, &reply);
        else if (result == 1)
            print_reply(&reply, record_reply(&stats, &reply));
    }
    print_stats(context, &stats); // TODO
    return (stats.received > 0 ? 0 : 1);
}