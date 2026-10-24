/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 16:18:50 by tat-nguy         ###   ########.fr       */
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

void print_help_more(const char *prog_name)
{
    fprintf(stderr, "Try '%s --help' for more information.\n", prog_name);
}

void report_ignored_packet(bool verbose, const char *reason)
{
    if (verbose)
        fprintf(stderr, "ft_ping: ignored packet: %s\n", reason);
}

void print_reply(const t_ping_reply *reply, bool duplicate)
{
    printf("%zu bytes from %s: icmp_seq=%u ttl=%u time=%.3f ms%s\n",
           reply->size, reply->src_ip, reply->sequence, reply->ttl,
           reply->rtt_ms, duplicate ? " (DUP!)" : "");
}

void print_header(const t_ping_context *context, uint16_t identifier)
{
    printf("PING %s (%s): %d data bytes\n", context->dest_name,
           context->dest_ip, PING_PAYLOAD_SIZE);
    if (context->op->verbose)
        printf(", id 0x%04x = %u", identifier, identifier);
    printf("\n");
}

void print_stats(const t_ping_context *context, const t_ping_stats *stats)
{
    double average;

    printf("--- %s ping statistics ---\n", context->dest_name);
    printf("%lu packets transmitted, %lu packets received, ",
           stats->transmitted, stats->received);

    if (stats->duplicates > 0)
        printf("+%lu duplicates, ", stats->duplicates);

    if (stats->transmitted > 0 && stats->transmitted > stats->received)
        printf("%lu%% packet loss", (stats->transmitted - stats->received) *
                                        100 / stats->transmitted);
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