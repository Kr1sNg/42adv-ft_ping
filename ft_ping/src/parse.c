/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/19 23:20:19 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int parse_args(int ac, char **av, t_ping_option *op)
{
    int i;

    op->verbose = false;
    op->dest = NULL;

    i = 1;
    while (i < ac)
    {
        if (strcmp(av[i], "-?") == 0 || strcmp(av[i], "--help") == 0)
        {
            print_help(av[0]);
            return (1);
        }
        else if (strcmp(av[i], "-v") == 0 || strcmp(av[i], "--verbose") == 0)
        {
            op->verbose = true;
        }
        else if (av[i][0] == '-')
        {
            fprintf(stderr, "%s: invalid option -- `%s`\n", av[0], av[i]);
            print_error(av[0]);
            return (-1);
        }
        else if (op->dest != NULL)
        {
            fprintf(stderr, "%s: too many destinations\n", av[0]);
            print_error(av[0]);
            return (-1);
        }
        else
        {
            op->dest = av[i];
        }
        i++;
    }
    if (op->dest == NULL)
    {
        fprintf(stderr, "%s: missing destination\n", av[0]);
        print_error(av[0]);
        return (-1);
    }
    return (0);
}