/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 12:11:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 16:22:36 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int validate_ip_header(const unsigned char *buffer, size_t received_size,
                       size_t *header_size, size_t *total_length)
{
    struct iphdr header;

    if (received_size < sizeof(header))
        return (1);

    memcpy(&header, buffer, sizeof(header));
    if (header.version != 4 || header.protocol != IPPROTO_ICMP)
        return (1);
    *header_size = (size_t)header.ihl * 4;
    if (*header_size < sizeof(header) || *header_size > received_size)
        return (1);
    *total_length = (size_t)ntohs(header.tot_len);
    if (*total_length > received_size)
        *total_length = received_size;
    if (*total_length < *header_size + sizeof(struct icmphdr))
        return 1;
    return 0;
}

int validate_icmp_error(const unsigned char *icmp, size_t icmp_size,
                        const t_recv_config *config, t_ping_reply *reply)
{
    const struct ip *original_ip;
    struct icmphdr original_icmp;
    size_t original_header_size;

    if (icmp_size < 2 * sizeof(struct icmphdr) + sizeof(struct iphdr))
        return 1;
    original_ip = (const struct ip *)(icmp + sizeof(struct icmphdr));
    original_header_size = (size_t)(icmp[sizeof(struct icmphdr)] & 0x0f) * 4;
    if (icmp_size < 2 * sizeof(struct icmphdr) + original_header_size)
        return 1;
    memcpy(&original_icmp, icmp + sizeof(struct icmphdr) + original_header_size,
           sizeof(original_icmp));
    if (ntohs(original_icmp.un.echo.id) != config->identifier)
        return 1;
    reply->kind = REPLY_ERROR;
    reply->original_ip = original_ip;
    return 0;
}

bool is_error_type(int type)
{
    return type == ICMP_DEST_UNREACH || type == ICMP_TIME_EXCEEDED ||
           type == ICMP_SOURCE_QUENCH || type == ICMP_REDIRECT ||
           type == ICMP_PARAMETERPROB;
}

int validate_icmp_reply(const unsigned char *buffer, size_t header_size,
                        size_t total_length, const t_recv_config *config,
                        t_ping_reply *reply)
{
    size_t icmp_size = total_length - header_size;
    struct icmphdr header;

    memcpy(&header, buffer + header_size, sizeof(header));
    reply->icmp_type = header.type;
    reply->icmp_code = header.code;
    if (is_error_type(header.type))
        return validate_icmp_error(buffer + header_size, icmp_size, config,
                                   reply);
    if (header.type != ICMP_ECHOREPLY || header.code != 0)
        return 1;
    if (ntohs(header.un.echo.id) != config->identifier)
        return 1;
    if (calculate_checksum(buffer + header_size, icmp_size) != 0)
        return 1;
    reply->kind = REPLY_ECHO;
    reply->sequence = ntohs(header.un.echo.sequence);
    return 0;
}

int extract_reply(const unsigned char *buffer, size_t header_size,
                  size_t total_length, const struct sockaddr_in *sender,
                  t_ping_reply *reply)
{
    struct iphdr header;

    memcpy(&header, buffer, sizeof(header));
    if (inet_ntop(AF_INET, &sender->sin_addr, reply->src_ip,
                  sizeof(reply->src_ip)) == NULL)
    {
        fprintf(stderr, "ft_ping: inet_ntop: %s\n", strerror(errno));
        return (-1);
    }
    reply->ttl = header.ttl;
    reply->size = total_length - header_size;
    return (0);
}

int wait_for_packet(int sockfd, double deadline_ms)
{
    struct timeval timeout;
    fd_set read_fds;
    int remaining;
    int result;

    while (!g_stop)
    {
        remaining = get_remaining_time(deadline_ms, &timeout);
        if (remaining <= 0)
            return remaining;
        FD_ZERO(&read_fds);
        FD_SET(sockfd, &read_fds);
        result = select(sockfd + 1, &read_fds, NULL, NULL, &timeout);
        if (result > 0)
            return 1;
        if (result == 0)
            continue;
        if (errno != EINTR)
        {
            perror("ft_ping: select");
            return -1;
        }
    }
    return 2;
}

int recv_echo_reply(const t_recv_config *config, t_ping_reply *reply)
{
    static unsigned char buffer[RECV_BUFFER_SIZE];
    struct sockaddr_in sender = {0};
    socklen_t sender_length = sizeof(sender);
    size_t received_size = 0;
    size_t header_size = 0;
    size_t total_length = 0;
    ssize_t bytes_received = 0;
    int result = 0;

    while (!g_stop)
    {
        result = wait_for_packet(config->sockfd, config->deadline_ms);
        if (result != 1)
            return result == 0 ? 1 : result;

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
                               &total_length) != 0)
            continue;
        if (validate_icmp_reply(buffer, header_size, total_length, config,
                                reply) != 0)
            continue;
        extract_rtt(buffer + header_size, total_length - header_size, reply);
        return extract_reply(buffer, header_size, total_length, &sender, reply);
    }
    return 2;
}