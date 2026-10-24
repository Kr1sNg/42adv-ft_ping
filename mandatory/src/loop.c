/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:50 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 16:14:56 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int send_ping(const t_ping_context *context, t_ping_stats *stats,
              uint16_t identifier, uint16_t *sequence)
{
    if (send_echo_req(context->sockfd, &context->dest, identifier, *sequence) ==
        -1)
        return (-1);

    stats->seen[*sequence] = false;
    (*sequence)++;
    stats->transmitted++;
    return (0);
}

void handle_reply(const t_ping_context *context, t_ping_stats *stats, t_ping_reply *reply)
{
    bool duplicate;
    (void)context;

    if (reply->kind == REPLY_ERROR)
    {
        printf("ft_ping: reply error");
        return;
    }
    duplicate = mark_sequence(stats, reply->sequence);
    if (duplicate)
        stats->duplicates++;
    else
    {
        stats->received++;
        record_rtt(stats, reply->rtt_ms);
    }
    print_reply(reply, duplicate);
}

bool mark_sequence(t_ping_stats *stats, uint16_t sequence)
{
    bool already_seen = stats->seen[sequence];
    
    stats->seen[sequence] = true;
    return already_seen;
}

int recv_until(const t_ping_context *context, t_ping_stats *stats, uint16_t identifier, double until_ms)
{
    t_recv_config config = {0};
    t_ping_reply reply = {0};
    int result = 0;

    config.sockfd = context->sockfd;
    config.identifier = identifier;
    config.deadline_ms = until_ms;
    
    result = recv_echo_reply(&config, &reply); // TODO
    if (result == 0)
        handle_reply(context, stats, &reply);
    if (result == 2)
        return (1);
    if (result == -1)
        return (-1);
    return (0);
}

int run_loop(const t_ping_context *context)
{
    t_ping_stats stats = {0};
    uint16_t identifier = (uint16_t)(getpid() & 0xffff);
    uint16_t sequence = 0;
    double now_ms;
    double next_send_ms;
    int result;

    print_header(context, identifier);
    if (get_time_ms(&next_send_ms) == -1)
        return (1);
    while (!g_stop)
    {
        if (get_time_ms(&now_ms) == -1)
            return (1);
        if (now_ms >= next_send_ms)
        {
            if (send_ping(context, &stats, identifier, &sequence) == -1)
                return (1);
            next_send_ms += PING_INTERVAL_MS;
        }
        result = recv_until(context, &stats, identifier, next_send_ms);

        if (result == -1)
            return 1;
        if (result == 1)
            break;
    }
    print_stats(context, &stats);
    return (stats.received > 0 ? 0 : 1);
}