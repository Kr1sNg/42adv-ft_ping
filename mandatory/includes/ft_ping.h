/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:46:59 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/24 22:03:30 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// RTT - Round-Trip Time

#ifndef FT_PING_H
#define FT_PING_H

#include "../libft/includes/libft.h"
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
#include <time.h>
#include <unistd.h>

#define _POSIX_C_SOURCE 200112L
#define PING_PAYLOAD_SIZE 56
#define PING_INTERVAL_MS 1000 /* time between two requests */
#define RECV_BUFFER_SIZE 65536

extern volatile sig_atomic_t g_stop;

// typedef enum e_ip_option
// {
//     IP_OPTION_NONE,
//     IP_OPTION_TS_ONLY,
//     IP_OPTION_TS_ADDR
// } t_ip_option;

typedef struct s_ping_option
{
    bool verbose;
    const char *dest;

    /* bonus */
    // bool flood;               /* -f : send every 10 ms, print '.' per request
    //                              and '\b' per reply (root only) */
    // bool numeric;             /* -n : print addresses as numbers, no reverse
    //                              DNS (used by --ip-timestamp=tsaddr) */
    // bool dont_route;          /* -r : bypass the routing table, only reach
    //                              hosts on a directly attached network */
    // unsigned long count;      /* -c : stop after sending N requests
    //                              (0 = until Ctrl-C) */
    // int ttl;                  /* --ttl : time-to-live of our packets, max
    //                              routers crossed (-1 = system default) */
    // int tos;                  /* -T : type of service byte of the IP header
    //                              (-1 = system default) */
    // unsigned long deadline_s; /* -w : stop after N seconds in total
    //                              (0 = no limit) */
    // unsigned long linger_s;   /* -W : seconds to wait for replies after the
    //                              last request (default 10) */
    // unsigned long preload;    /* -l : send N requests at once before the
    //                              normal rhythm (root only) */
    // size_t payload_size;      /* -s : bytes of data after the ICMP header
    //                              (default 56) */
    // unsigned char pattern[PING_MAX_PATTERN]; /* -p : hex bytes repeated to
    //                                             fill the data */
    // size_t pattern_size;   /* -p : number of bytes in pattern */
    // t_ip_option ip_option; /* --ip-timestamp : ask routers to write
    //                           timestamps (tsonly / tsaddr) */
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
    size_t size;                  /* ICMP bytes, as printed by ping */
    uint16_t sequence;
    double rtt_ms;
    uint8_t icmp_type;            /* for errors: which error */
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
    double total_rtt_squared; /* for stddev */
    bool seen[65536];
} t_ping_stats;

void print_help(const char *prog_name);
void print_help_more(const char *prog_name);
void report_ignored_packet(bool verbose, const char *reason);
void print_reply(const t_ping_reply *reply, bool duplicate);
void print_header(const t_ping_context *context, uint16_t identifier);
void print_stats(const t_ping_context *context, const t_ping_stats *stats);

void fill_payload(unsigned char *payload);

int parse_args(int ac, char **av, t_ping_option *op);

int extract_reply(const unsigned char *buffer, size_t header_size,
                  size_t total_length, const struct sockaddr_in *sender,
                  t_ping_reply *reply);
int send_echo_req(int sockfd, const struct sockaddr_in *dest, uint16_t identifier,
                  uint16_t sequence);
uint16_t calculate_checksum(const void *data, size_t length);

// network
int resolve_dest(const char *dest, struct sockaddr_in *addr, char *ip_str,
                 size_t ip_str_size);
int create_icmp_socket(void);

// loop.c
int send_ping(const t_ping_context *context, t_ping_stats *stats,
              uint16_t identifier, uint16_t *sequence);
bool mark_sequence(t_ping_stats *stats, uint16_t sequence);
int recv_until(const t_ping_context *context, t_ping_stats *stats,
               uint16_t identifier, double until_ms);
void handle_reply(const t_ping_context *context, t_ping_stats *stats,
                  t_ping_reply *reply);
int run_loop(const t_ping_context *ctxt);

// receive.c
int wait_for_packet(int sockfd, double deadline_ms);
int validate_ip_header(const unsigned char *buffer, size_t received_size,
                       size_t *header_size, size_t *total_length);
int validate_icmp_error(const unsigned char *icmp, size_t icmp_size,
                        const t_recv_config *config, t_ping_reply *reply);
int validate_icmp_reply(const unsigned char *buffer, size_t header_size,
                        size_t total_length, const t_recv_config *config,
                        t_ping_reply *reply);
bool is_error_type(int type);
int extract_reply(const unsigned char *buffer, size_t header_size,
                  size_t total_length, const struct sockaddr_in *sender,
                  t_ping_reply *reply);
int recv_echo_reply(const t_recv_config *config, t_ping_reply *reply);

// signal.c
void sigint_handler(int signum);
int handle_signal(void);

// time.c
int get_time_ms(double *ms);
double timespec_to_ms(const struct timespec *time);
void record_rtt(t_ping_stats *stats, double rtt_ms);
int get_remaining_time(double deadline_ms, struct timeval *timeout);
void extract_rtt(const unsigned char *icmp, size_t icmp_size,
                 t_ping_reply *reply);

#endif