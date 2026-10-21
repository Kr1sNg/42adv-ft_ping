/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/20 11:48:20 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int resolve_dest(const char *dest, struct sockaddr_in *addr, char *ip_str,
                 size_t ip_str_size)
{
    struct addrinfo hints;
    struct addrinfo *result;
    int status;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM;

    status = getaddrinfo(dest, NULL, &hints, &result);
    if (status != 0)
    {
        fprintf(stderr, "ft_ping: %s: %s\n", dest, gai_strerror(status));
        return (-1);
    }
    
    if (result->ai_addrlen < sizeof(*addr))
    {
        fprintf(stderr, "ft_ping: invalid IPv4 address result\n");
        freeaddrinfo(result);
        return (-1);
    }

    memcpy(addr, result->ai_addr, sizeof(*addr));

    if (inet_ntop(AF_INET, &addr->sin_addr, ip_str, ip_str_size) == NULL)
    {
        fprintf(stderr, "ft_ping: inet_ntop: %s\n", strerror(errno));
        freeaddrinfo(result);
        return (-1);
    }
    
    freeaddrinfo(result);
    return (0);
}