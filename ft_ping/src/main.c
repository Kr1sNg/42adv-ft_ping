/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:48:58 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/19 22:24:25 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int main(int ac, char **av)
{
    t_ping_option op;
    int result;

    result = parse_args(ac, av, &op);

    if (result == 1)
        return (0);
    if (result == -1)
        return (2);

    printf("ft_ping: destination = %s\n", op.dest);
    printf("ft_ping: verbose = %s\n", op.verbose ? "enabled" : "disabled");

    return (0);
}