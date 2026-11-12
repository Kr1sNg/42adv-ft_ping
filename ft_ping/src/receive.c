/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:11:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:02:31 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// A raw ICMP socket receives EVERY ICMP packet reaching the machine
// (our own requests on loopback, other ping processes...). We keep only:
//   - an Echo Reply carrying our identifier
//   - an ICMP error whose embedded packet carries our identifier:
//     [ICMP error header (8)][our IP header][our ICMP header (8)]

#include "../includes/ft_ping.h"

// Wait until the socket is readable or next_send_ms is reached.
// Returns 1 (readable), 0 (next_send_ms or Ctrl-C) or -1 (error).
static int wait_for_packet(int sockfd, double next_send_ms)
{
    double remaining_ms = next_send_ms - now_ms();
    if (remaining_ms <= 0.0)
        return (0);

    struct timeval timeout;
    timeout.tv_sec = (time_t)(remaining_ms / 1000.0);
    timeout.tv_usec =
        (suseconds_t)((remaining_ms - timeout.tv_sec * 1000.0) * 1000.0);

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(sockfd, &read_fds);

    int result = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
    if (result == -1 && errno != EINTR)
    {
        fprintf(stderr, "ft_ping: select: %s\n", strerror(errno));
        return (-1);
    }
    return (result > 0);
}

// Is this an Echo Reply to one of our requests? If so, compute its RTT
// (Round-Trip Time).
static bool parse_echo_reply(const unsigned char *icmp, size_t icmp_size,
                             uint16_t identifier, t_ping_reply *reply)
{
    struct icmphdr header;
    memcpy(&header, icmp, sizeof(header));

    struct timespec sent;
    if (ntohs(header.un.echo.id) != identifier ||
        icmp_size < sizeof(header) + sizeof(sent) ||
        calculate_checksum(icmp, icmp_size) != 0)
        return (false);

    memcpy(&sent, icmp + sizeof(header), sizeof(sent));
    reply->is_error = false;
    reply->sequence = ntohs(header.un.echo.sequence);
    reply->rtt_ms = now_ms() - timespec_to_ms(&sent);
    return (true);
}

// Is this ICMP error caused by one of our requests? true -> error caused our
// req
static bool parse_echo_error(const unsigned char *icmp, size_t icmp_size,
                             uint16_t identifier, t_ping_reply *reply)
{
    if (icmp_size < 2 * sizeof(struct icmphdr) + sizeof(struct ip))
        return (false);

    const struct ip *original_ip =
        (const struct ip *)(icmp + sizeof(struct icmphdr));
    size_t original_header_size = (size_t)original_ip->ip_hl * 4;
    if (icmp_size < 2 * sizeof(struct icmphdr) + original_header_size)
        return (false);

    struct icmphdr original_icmp;
    memcpy(&original_icmp, icmp + sizeof(struct icmphdr) + original_header_size,
           sizeof(original_icmp));

    if (ntohs(original_icmp.un.echo.id) != identifier)
        return (false);

    reply->is_error = true;
    reply->original_ip = original_ip;
    return (true);
}

// Look at one recieved packet: true if it's belong to us (reply is filled)
static bool parse_packet(const unsigned char *buffer, size_t size,
                         uint16_t identifier, t_ping_reply *reply)
{
    if (size < sizeof(struct ip))
        return (false);

    bool is_ours = false;
    const struct ip *ip = (const struct ip *)buffer;
    size_t header_size = (size_t)ip->ip_hl * 4;
    if (header_size < sizeof(struct ip) ||
        size < header_size + sizeof(struct icmphdr))
        return (false);

    const unsigned char *icmp = buffer + header_size;
    reply->icmp_type = icmp[0];
    reply->icmp_code = icmp[1];
    if (icmp[0] == ICMP_ECHOREPLY)
        is_ours = parse_echo_reply(icmp, size - header_size, identifier, reply);
    else if (icmp[0] == ICMP_DEST_UNREACH || icmp[0] == ICMP_TIME_EXCEEDED)
        is_ours = parse_echo_error(icmp, size - header_size, identifier, reply);
    else
        is_ours = false;

    if (!is_ours)
        return (false);

    inet_ntop(AF_INET, &ip->ip_src, reply->src_ip, sizeof(reply->src_ip));
    reply->ttl = ip->ip_ttl;
    reply->size = size - header_size;
    return (true);
}

// Wait until deadline_ms for ONE packet that belongs to us.
// Returns 1 (reply filled), 0 (next_send_ms or Ctrl-C) or -1 (error).
// The buffer is static: reply->original_ip stays valid until the next call.
int recv_echo_reply(int sockfd, uint16_t identifier, double next_send_ms,
                    t_ping_reply *reply)
{
    static unsigned char buffer[RECV_BUFFER_SIZE];
    ssize_t bytes_received = 0;
    int result = 0;

    while (!g_stop)
    {
        result = wait_for_packet(sockfd, next_send_ms);
        if (result != 1)
            return (result);

        bytes_received =
            recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
        if (bytes_received == -1)
        {
            if (errno == EINTR)
                continue;
            fprintf(stderr, "ft_ping: recvfrom: %s\n", strerror(errno));
            return (-1);
        }
        if (parse_packet(buffer, (size_t)bytes_received, identifier, reply))
            return (1);
    }
    return (0);
}