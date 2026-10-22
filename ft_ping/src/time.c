/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:19:08 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/22 15:17:27 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int get_time_ms(double *ms)
{
    struct timespec now;
    *ms = (double)now.tv_sec * 1000.0 + (double)now.tv_nsec / 1000000.0;
    return (0);
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
