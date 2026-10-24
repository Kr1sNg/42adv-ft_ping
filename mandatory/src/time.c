/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:19:08 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 16:33:05 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int get_time_ms(double *ms)
{
    struct timespec now;
    if (clock_gettime(CLOCK_MONOTONIC, &now) == -1)
    {
        fprintf(stderr, "ft_ping: get_time_ms: clock_gettime: %s\n",
                strerror(errno));
        return (-1);
    }
    *ms = (double)now.tv_sec * 1000.0 + (double)now.tv_nsec / 1000000.0;
    return (0);
}

double timespec_to_ms(const struct timespec *time)
{
    return (double)time->tv_sec * 1000.0 + (double)time->tv_nsec / 1000000.0;
}

void record_rtt(t_ping_stats *stats, double rtt_ms)
{
    stats->received++;
    if (stats->received == 1 || rtt_ms < stats->min_rtt)
        stats->min_rtt = rtt_ms;
    if (stats->received == 1 || rtt_ms > stats->max_rtt)
        stats->max_rtt = rtt_ms;
    stats->totat_rtt += rtt_ms;
}

int get_remaining_time(double deadline_ms, struct timeval *timeout)
{
    struct timespec now;
    double remaining_ms;

    clock_gettime(CLOCK_MONOTONIC, &now);
    remaining_ms = deadline_ms - timespec_to_ms(&now);
    if (remaining_ms <= 0.0)
        return (0);
    timeout->tv_sec = (time_t)(remaining_ms / 1000.0);
    timeout->tv_usec = (suseconds_t)((remaining_ms
        - (double)timeout->tv_sec * 1000.0) * 1000.0);
    return (1);
}

/* RTT = now - send time that we stored in the payload */
void extract_rtt(const unsigned char *icmp, size_t icmp_size, t_ping_reply *reply)
{
    struct timespec sent;
    struct timespec now;

    if (reply->kind != REPLY_ECHO || icmp_size < sizeof(struct icmphdr) + sizeof(sent))
        return;
    
    memcpy(&sent, icmp + sizeof(struct icmphdr), sizeof(sent));
    clock_gettime(CLOCK_MONOTONIC, &now);
    reply->rtt_ms = timespec_to_ms(&now) - timespec_to_ms(&sent);
}
