/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:48:58 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:04:20 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

volatile sig_atomic_t g_stop = false;

int main(int ac, char **av)
{
    t_ping_option op = {0};
    t_ping_context context = {0};
    char ip_str[INET_ADDRSTRLEN];

    int result = parse_args(ac, av, &op);
    if (result == 1)
        return (EXIT_SUCCESS);
    if (result == -1)
        return (EXIT_USAGE);

    if (resolve_dest(op.dest, &context.dest, ip_str, sizeof(ip_str)) == -1)
        return (EXIT_FAILURE);

    context.sockfd = create_icmp_socket();
    if (context.sockfd == -1)
        return (EXIT_FAILURE);

    if (handle_signal() == -1)
    {
        if (close(context.sockfd) == -1)
            fprintf(stderr, "ft_ping: closefd: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }

    context.dest_name = op.dest;
    context.dest_ip = ip_str;
    context.op = &op;

    result = run_loop(&context);

    if (close(context.sockfd) == -1)
    {
        fprintf(stderr, "ft_ping: closefd: %s\n", strerror(errno));
        return (EXIT_FAILURE);
    }

    return (result);
}