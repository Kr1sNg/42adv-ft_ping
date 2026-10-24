/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/22 12:35:33 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 10:37:13 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void sigint_handler(int signum)
{
    (void)signum;
    g_stop = true;
}

int handle_signal(void)
{
    struct sigaction action;

    memset(&action, 0, sizeof(action));
    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);

    if (sigaction(SIGINT, &action, NULL) == -1)
    {
        fprintf(stderr, "ft_ping: sigaction: %s\n", strerror(errno));
        return (-1);
    }
    return (0);
}