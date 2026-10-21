/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:48:58 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/21 16:36:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

static volatile sig_atomic_t g_stop = false;

static void sigint_handler(int signum)
{
    (void)signum;
    g_stop = true;
}

int main(int ac, char **av)
{
    t_ping_option op;
    struct sockaddr_in dest_addr;
    struct timeval timeout;
    char ip_str[INET_ADDRSTRLEN];
    char reply_ip[INET_ADDRSTRLEN];
    unsigned short identifier;
    size_t reply_size;
    int result;
    int sockfd;

    result = parse_args(ac, av, &op);
    if (result == 1)
        return (0);
    if (result == -1)
        return (2);

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;

    if (resolve_dest(op.dest, &dest_addr, ip_str, sizeof(ip_str)) == -1)
        return (2);

    sockfd = create_icmp_socket();
    if (sockfd == -1)
        return (2);

    timeout.tv_sec = 1;
    timeout.tv_usec = 0;

    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout,
                   sizeof(timeout)) == -1)
    {
        fprintf(stderr, "ft_ping: setsockopt: %s\n", strerror(errno));
        close(sockfd);
        return (1);
    }

    identifier = (unsigned short)(getpid() & 0xffff);
    printf("ft_ping: destination = %s (%s)\n", op.dest, ip_str);

    result = send_echo_req(sockfd, &dest_addr, identifier, 1);
    if (result == 0)
    {
        result = recv_echo_reply(sockfd, identifier, 1, reply_ip,
                                 sizeof(reply_ip), &reply_size);
        if (result == 0)
        {
            printf("ft_ping: reply from %s: %zu bytes of ICMP message\n", reply_ip, reply_size);
        }
        else if (result == 1)
        {
            printf("ft_ping: request timed out\n");
        }
    }

    if (close(sockfd) == -1)
    {
        fprintf(stderr, "ft_ping: close: %s\n", strerror(errno));
        return (1);
    }

    if (result == -1)
        return (1);

    // printf("ft_ping: destination = %s\n", op.dest);
    // printf("ft_ping: IPv4 address = %s\n", ip_str);
    // printf("ft_ping: raw ICMP socket created (fd=%d)\n", sockfd);
    // printf("ft_ping: verbose = %s\n", op.verbose ? "enabled" : "disabled");

    return (0);
}