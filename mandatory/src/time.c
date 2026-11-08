/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:19:08 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:08:50 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

double timespec_to_ms(const struct timespec *time)
{
    return (double)time->tv_sec * 1000.0 + (double)time->tv_nsec / 1000000.0;
}

// Current time in milliseconds. CLOCK_MONOTONIC never jumps (unlike the
// wall clock), and clock_gettime() cannot fail with a valid clock and a
// valid pointer, so there is no error to handle.
double now_ms(void)
{
    struct timespec now;

    clock_gettime(CLOCK_MONOTONIC, &now);
    return (timespec_to_ms(&now));
}