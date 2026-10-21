/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:46:59 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/21 16:27:57 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#define _POSIX_C_SOURCE 200112L
#define PING_PAYLOAD_SIZE 32
#define PING_INTERVAL_MS 1000
#define REPLY_TIMEOUT_MS 1000

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>

typedef struct s_ping_option
{
    bool verbose;
    const char *dest;
} t_ping_option;

void print_help(const char *prog_name);
void print_help_more(const char *prog_name);
int parse_args(int ac, char **av, t_ping_option *op);

int resolve_dest(const char *dest, struct sockaddr_in *addr, char *ip_str,
                 size_t ip_str_size);

int create_icmp_socket(void);

int send_echo_req(int sockfd, struct sockaddr_in *dest,
                  unsigned short identifier, unsigned short sequence);
unsigned short calculate_checksum(const unsigned char *data, size_t length);
int recv_echo_reply(int sockfd, unsigned short identifier,
                    unsigned short sequence, char *src_ip, size_t src_ip_size,
                    size_t *reply_size);

#endif