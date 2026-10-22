/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/22 18:03:49 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void print_help(const char *prog_name)
{
    printf(
        "    \n"
        "Usage\n"
        "  %s [options] <destination>\n"
        "\n"
        "Options:\n"
        "  <destination>      DNS name or IP address\n"
        "  -3                 RTT precision (do not round up the result time)\n"
        "  -a                 use audible ping\n"
        "  -A                 use adaptive ping\n"
        "  -B                 sticky source address\n"
        "  -c <count>         stop after <count> replies\n"
        "  -C                 call connect() syscall on socket creation\n"
        "  -D                 print timestamps\n"
        "  -d                 use SO_DEBUG socket option\n"
        "  -e <identifier>    define identifier for ping session, default is "
        "random for\n"
        "                     SOCK_RAW and kernel defined for SOCK_DGRAM\n"
        "                     Imply using SOCK_RAW (for IPv4 only for "
        "identifier 0)\n"
        "  -f                 flood ping\n"
        "  -h                 print help and exit\n"
        "  -H                 force reverse DNS name resolution (useful for "
        "numeric\n"
        "                     destinations or for -f), override -n\n"
        "  -I <interface>     either interface name or address\n"
        "  -i <interval>      seconds between sending each packet\n"
        "  -L                 suppress loopback of multicast packets\n"
        "  -l <preload>       send <preload> number of packages while waiting "
        "replies\n"
        "  -m <mark>          tag the packets going out\n"
        "  -M <pmtud opt>     define path MTU discovery, can be one of "
        "<do|dont|want|probe>\n"
        "  -n                 no reverse DNS name resolution, override -H\n"
        "  -O                 report outstanding replies\n"
        "  -p <pattern>       contents of padding byte\n"
        "  -q                 quiet output\n"
        "  -Q <tclass>        use quality of service <tclass> bits\n"
        "  -s <size>          use <size> as number of data bytes to be sent\n"
        "  -S <size>          use <size> as SO_SNDBUF socket option value\n"
        "  -t <ttl>           define time to live\n"
        "  -U                 print user-to-user latency\n"
        "  -v, --verbose      verbose output\n"
        "  -V                 print version and exit\n"
        "  -w <deadline>      reply wait <deadline> in seconds\n"
        "  -W <timeout>       time to wait for response\n"
        "  -?, --help         give this help list\n"
        "\n"
        "Report bugs to the author. Thanks 💖\n",
        prog_name);
}

void print_help_more(const char *prog_name)
{
    fprintf(stderr, "Try `%s -?` for more information.\n", prog_name);
}

void report_ignored_packet(bool verbose, const char *reason)
{
    if (verbose)
        fprintf(stderr, "ft_ping: ignored packet: %s\n", reason);
}

void print_reply(const t_ping_reply *reply, uint16_t sequence, double rtt_ms)
{
    printf("%zy bytes from %s: icmp_seq=%u ttl=%u time=%.3f ms\n", reply->size,
           reply->src_ip, sequence, reply->ttl, rtt_ms);
}