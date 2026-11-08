/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:46:59 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:45:25 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RTT - Round-Trip Time

#ifndef FT_PING_H
#define FT_PING_H

#include "../libft/includes/libft.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#define PING_PAYLOAD_SIZE 56
#define PING_INTERVAL_MS 1000 /* time between two requests */
#define RECV_BUFFER_SIZE 65536
#define EXIT_USAGE 64

extern volatile sig_atomic_t g_stop;

typedef struct s_ping_option
{
    bool verbose; // -v
    const char *dest;
} t_ping_option;

typedef struct s_recv_config
{
    int sockfd;
    uint16_t identifier;
    double deadline_ms;
} t_recv_config;

/* One packet that belongs to us: an Echo Reply or an ICMP error */
typedef struct s_ping_reply
{
    bool is_error;                /* false: Echo Reply, true: ICMP error */
    char src_ip[INET_ADDRSTRLEN]; /* who sent it */
    uint8_t ttl;
    size_t size; /* ICMP bytes, as printed by ping */
    uint16_t sequence;
    double rtt_ms;
    uint8_t icmp_type; /* for errors: which error */
    uint8_t icmp_code;
    const struct ip *original_ip; /* for errors: our packet inside it */
} t_ping_reply;

typedef struct s_ping_context
{
    int sockfd;
    struct sockaddr_in dest;
    const char *dest_name;
    const char *dest_ip;
    const t_ping_option *op;
} t_ping_context;

typedef struct s_ping_stats
{
    unsigned long transmitted;
    unsigned long received;
    unsigned long duplicates;
    double min_rtt;
    double max_rtt;
    double totat_rtt;
    double total_rtt_squared;
    bool seen[65536];
} t_ping_stats;

// loop.c

uint16_t calculate_checksum(const void *data, size_t length);
int run_loop(const t_ping_context *context);

// network.c

int resolve_dest(const char *dest, struct sockaddr_in *addr, char *ip_str,
                 size_t ip_str_size);
int create_icmp_socket(void);

// parse.c

int parse_args(int ac, char **av, t_ping_option *op);

// print.c

void print_help(const char *prog_name);
void print_header(const t_ping_context *context, uint16_t identifier);
void print_error(const t_ping_context *context, const t_ping_reply *reply);
void print_reply(const t_ping_reply *reply, bool duplicate);
void print_stats(const t_ping_context *context, const t_ping_stats *stats);

// receive.c

int recv_echo_reply(int sockfd, uint16_t identifier, double next_send_ms,
                    t_ping_reply *reply);

// signal.c

int handle_signal(void);

// time.c

double timespec_to_ms(const struct timespec *time);
double now_ms(void);

#endif