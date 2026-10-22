/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:46:59 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/22 19:33:31 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RTT - Round-Trip Time

#ifndef FT_PING_H
#define FT_PING_H

#define _POSIX_C_SOURCE 200112L
#define PING_PAYLOAD_SIZE 56
#define PING_MAX_PAYLOAD 65399    /* biggest -s accepted by inetutils */
#define PING_INTERVAL_MS 1000     /* time between two requests */
#define PING_FLOOD_INTERVAL_MS 10 /* same, with -f */
#define PING_LINGER_S 10          /* -W default: wait after last send */
#define PING_MAX_PATTERN 16
#define RECV_BUFFER_SIZE 65536

#include <arpa/inet.h>
#include <bits/time.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <unistd.h>

extern volatile sig_atomic_t g_stop;

typedef enum e_ip_option
{
    IP_OPTION_NONE,
    IP_OPTION_TS_ONLY,
    IP_OPTION_TS_ADDR
} t_ip_option;

typedef struct s_ping_option
{
    bool verbose;
    const char *dest;

    /* bonus */
    bool flood;               /* -f : send every 10 ms, print '.' per request
                                 and '\b' per reply (root only) */
    bool numeric;             /* -n : print addresses as numbers, no reverse
                                 DNS (used by --ip-timestamp=tsaddr) */
    bool dont_route;          /* -r : bypass the routing table, only reach
                                 hosts on a directly attached network */
    unsigned long count;      /* -c : stop after sending N requests
                                 (0 = until Ctrl-C) */
    int ttl;                  /* --ttl : time-to-live of our packets, max
                                 routers crossed (-1 = system default) */
    int tos;                  /* -T : type of service byte of the IP header
                                 (-1 = system default) */
    unsigned long deadline_s; /* -w : stop after N seconds in total
                                 (0 = no limit) */
    unsigned long linger_s;   /* -W : seconds to wait for replies after the
                                 last request (default 10) */
    unsigned long preload;    /* -l : send N requests at once before the
                                 normal rhythm (root only) */
    size_t payload_size;      /* -s : bytes of data after the ICMP header
                                 (default 56) */
    unsigned char pattern[PING_MAX_PATTERN]; /* -p : hex bytes repeated to
                                                fill the data */
    size_t pattern_size;   /* -p : number of bytes in pattern */
    t_ip_option ip_option; /* --ip-timestamp : ask routers to write
                              timestamps (tsonly / tsaddr) */
} t_ping_option;

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
    unsigned long errors;
    double min_rtt;
    double max_rtt;
    double totat_rtt;
    double total_rtt_squared;      /* for stddev */
    unsigned char seen[65536 / 8]; /* one bit per sequence: DUP! */
} t_ping_stats;

typedef struct s_recv_config
{
    int sockfd;
    uint16_t identifier;
    uint16_t sequence;
    unsigned int timeout_ms;
    size_t payload_size;
} t_recv_config;

typedef enum e_reply_kind
{
    REPLY_ECHO,
    REPLY_ERROR
} t_reply_kind;

typedef struct s_ping_reply
{
    t_reply_kind kind;
    char src_ip[INET_ADDRSTRLEN];
    uint8_t ttl;
    size_t size;
    uint16_t sequence;
    bool has_rtt;
    double rtt_ms;
    uint8_t icmp_type;
    uint8_t icmp_code;
    const struct ip *original_ip;
    const unsigned char *ip_options;
    size_t ip_options_size;
} t_ping_reply;

void print_help(const char *prog_name);
void print_help_more(const char *prog_name);
void report_ignored_packet(bool verbose, const char *reason);
void print_reply(const t_ping_reply *reply, uint16_t sequence, double rtt_ms);

int parse_args(int ac, char **av, t_ping_option *op);

int resolve_dest(const char *dest, struct sockaddr_in *addr, char *ip_str,
                 size_t ip_str_size);

int create_icmp_socket(void);

int send_echo_req(int sockfd, struct sockaddr_in *dest, uint16_t identifier,
                  uint16_t sequence);
uint16_t calculate_checksum(const uint8_t *data, size_t length);
int recv_echo_reply(int sockfd, uint16_t identifier, uint16_t sequence,
                    char *src_ip, size_t src_ip_size, size_t *reply_size);

int process_one_ping(const t_ping_context *context, uint16_t identifier,
                     uint16_t sequence, t_ping_stats *stats,
                     double request_start_ms);
int run_loop(const t_ping_context *ctxt);

// signal.c
void sigint_handler(int signum);
int signal_handle(void);

int get_time_ms(double *ms);
void record_rtt(t_ping_stats *stats, double rtt_ms);

#endif