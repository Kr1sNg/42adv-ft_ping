/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   network.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:03:39 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int resolve_dest(const char *dest, struct sockaddr_in *addr, char *ip_str,
                 size_t ip_str_size)
{
    struct addrinfo hints = {0};
    struct addrinfo *result = NULL;

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    int status = getaddrinfo(dest, NULL, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "ft_ping: unknown host\n");
        return (-1);
    }

    memcpy(addr, result->ai_addr, sizeof(*addr));
    freeaddrinfo(result);
    if (inet_ntop(AF_INET, &addr->sin_addr, ip_str, ip_str_size) == NULL)
    {
        fprintf(stderr, "ft_ping: inet_ntop: %s\n", strerror(errno));
        return (-1);
    }
    return (0);
}

int create_icmp_socket(void)
{
    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd == -1)
    {
        if (errno == EPERM || errno == EACCES)
            fprintf(stderr, "ft_ping: Lacking privilege for icmp socket.\n");
        else
            fprintf(stderr, "ft_ping: socket: %s\n", strerror(errno));
        return (-1);
    }
    return (sockfd);
}