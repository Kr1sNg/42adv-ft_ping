/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/11/08 17:15:04 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

void print_help(const char *prog_name)
{
    printf("    \n"
           "Usage: %s [OPTION...] HOST ...\n"
           "Send ICMP ECHO_REQUEST packets to network hosts.\n"
           "\n"
           " Options valid for all request types:\n"
           "  -v, --verbose              verbose output\n"
           "\n"
           "  -?, --help                 give this help list\n"
           "\n"
           "Report bugs to tat-nguy 💖\n",
           prog_name);
}

// "PING google.com (142.250.74.174): 56 data bytes"
void print_header(const t_ping_context *context, uint16_t identifier)
{
    printf("PING %s (%s): %d data bytes", context->dest_name, context->dest_ip,
           PING_PAYLOAD_SIZE);
    if (context->op->verbose)
        printf(", id 0x%04x = %u", identifier, identifier);
    printf("\n");
}

static const char *describe_error(int type, int code)
{
    static const char *unreachable[] = {
        "Destination Net Unreachable",      "Destination Host Unreachable",
        "Destination Protocol Unreachable", "Destination Port Unreachable",
        "Fragmentation needed and DF set",  "Source Route Failed"};

    if (type == ICMP_TIME_EXCEEDED)
        return (code == 0 ? "Time to live exceeded"
                          : "Frag reassembly time exceeded");
    if (code >= 0 && code < 6)
        return (unreachable[code]);
    return ("Destination Unreachable");
}

// -v: dump the IP header + ICMP header of OUR request found in the error
static void print_ip_header_dump(const struct ip *ip)
{
    const unsigned char *bytes = (const unsigned char *)ip;
    const struct icmphdr *icmp;
    size_t header_size = (size_t)ip->ip_hl * 4;
    size_t i = 0;
    char src[INET_ADDRSTRLEN];
    char dst[INET_ADDRSTRLEN];

    printf("IP Hdr Dump:\n ");
    while (i + 1 < header_size)
    {
        printf("%02x%02x ", bytes[i], bytes[i + 1]);
        i += 2;
    }
    printf("\nVr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
    inet_ntop(AF_INET, &ip->ip_src, src, sizeof(src));
    inet_ntop(AF_INET, &ip->ip_dst, dst, sizeof(dst));
    printf(" %1x  %1x  %02x %04x %04x   %1x %04x  %02x  %02x %04x %s  %s \n",
           ip->ip_v, ip->ip_hl, ip->ip_tos, ntohs(ip->ip_len), ntohs(ip->ip_id),
           (ntohs(ip->ip_off) & 0xe000) >> 13, ntohs(ip->ip_off) & 0x1fff,
           ip->ip_ttl, ip->ip_p, ntohs(ip->ip_sum), src, dst);
    icmp = (const struct icmphdr *)(bytes + header_size);
    printf("ICMP: type %u, code %u, size %u, id 0x%04x, seq 0x%04x\n",
           icmp->type, icmp->code,
           (unsigned int)(ntohs(ip->ip_len) - header_size),
           ntohs(icmp->un.echo.id), ntohs(icmp->un.echo.sequence));
}

// "92 bytes from 192.168.1.1: Time to live exceeded" (+ dump with -v)
void print_error(const t_ping_context *context, const t_ping_reply *reply)
{
    printf("%zu bytes from %s: %s\n", reply->size, reply->src_ip,
           describe_error(reply->icmp_type, reply->icmp_code));
    if (context->op->verbose)
        print_ip_header_dump(reply->original_ip);
}

// "64 bytes from 127.0.0.1: icmp_seq=0 ttl=64 time=0.042 ms"
void print_reply(const t_ping_reply *reply, bool duplicate)
{
    printf("%zu bytes from %s: icmp_seq=%u ttl=%u time=%.3f ms%s\n",
           reply->size, reply->src_ip, reply->sequence, reply->ttl,
           reply->rtt_ms, duplicate ? " (DUP!)" : "");
}

void print_stats(const t_ping_context *context, const t_ping_stats *stats)
{
    double average;

    printf("--- %s ft_ping statistics ---\n", context->dest_name);
    printf("%lu packets transmitted, %lu packets received, ",
           stats->transmitted, stats->received);
    if (stats->duplicates > 0)
        printf("+%lu duplicates, ", stats->duplicates);
    if (stats->transmitted > 0 && stats->received <= stats->transmitted)
        printf("%lu%% packet loss",
               (stats->transmitted - stats->received) * 100 / stats->transmitted);
    printf("\n");
    if (stats->received > 0)
    {
        average = stats->totat_rtt / (double)stats->received;
        printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n",
               stats->min_rtt, average, stats->max_rtt,
               ft_sqrt(stats->total_rtt_squared / (double)stats->received -
                       ft_pow_int(average, 2)));
    }
}