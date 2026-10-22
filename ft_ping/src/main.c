/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:48:58 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/22 19:34:31 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

volatile sig_atomic_t g_stop = false;

int main(int ac, char **av)
{
    t_ping_option op;
    t_ping_context ctxt;
    char ip_str[INET_ADDRSTRLEN];
    int result;

    result = parse_args(ac, av, &op);
    if (result == 1)
        return (0);
    if (result == -1)
        return (64);
    if (result == 2)
        return (1);

    memset(&ctxt, 0, sizeof(ctxt));
    ctxt.dest.sin_family = AF_INET;

    if (resolve_dest(op.dest, &ctxt.dest, ip_str, sizeof(ip_str)) == -1)
        return (1);

    ctxt.sockfd = create_icmp_socket(&op);  // TODO
    if (ctxt.sockfd == -1)
        return (1);

    if (signal_handle() == -1)
    {
        if (close(ctxt.sockfd) == -1)
            fprintf(stderr, "ft_ping: closefd: %s\n", strerror(errno));
        return (1);
    }

    ctxt.dest_name = op.dest;
    ctxt.dest_ip = ip_str;
    ctxt.op = &op;

    result = run_loop(&ctxt);

    if (close(ctxt.sockfd) == -1)
    {
        fprintf(stderr, "ft_ping: closefd: %s\n", strerror(errno));
        return (1);
    }
    return (result);
}