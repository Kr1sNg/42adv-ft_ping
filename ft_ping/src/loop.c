/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 17:18:50 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/22 18:03:49 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ping.h"

int process_one_ping(const t_ping_context *ctxt, uint16_t identifier,
                     uint16_t sequence, t_ping_stats *stats,
                     double request_start_ms)
{
    t_recv_config config;
    t_ping_reply reply;
    double reply_time_ms;
    double rtt_ms;
    int result;

    if (send_echo_req(ctxt->sockfd, &ctxt->dest, identifier, sequence) == -1)
        return (-1);

    stats->transmitted++;
    config.sockfd = ctxt->sockfd;
    config.identifier = identifier;
    config.sequence = sequence;
    config.timeout_ms = REPLY_TIMEOUT_MS;
    config.verbose = ctxt->verbose;
    result = recv_echo_reply(&config, &reply); // TODO
    if (result == 1)
    {
        print_timeout(sequence);
        return (0);
    }
    if (result == 2)
        return 1;
    if (result == -1)
        return -1;
    if (get_time_ms(&reply_time_ms) == -1)
        return (-1);
    rtt_ms = reply_time_ms - request_start_ms;
    record_rtt(stats, rtt_ms);
    print_reply(&reply, sequence, rtt_ms);
    return (0);
}

int run_loop(const t_ping_context *ctxt)
{
    t_ping_stats stats = {0, 0, 0.0, 0.0, 0.0};
    uint16_t identifier = (uint16_t)(getpid() & 0xffff);
    uint16_t sequence = 0;
    int exit_status = 0;
    double request_start_ms;
    int result;

    printf("PING %s (%s) %d(%d) bytes of data.\n", ctxt->dest_name,
           ctxt->dest_ip, PING_PAYLOAD_SIZE,
           PING_PAYLOAD_SIZE + (int)sizeof(struct icmphdr) + 20);
    while (!g_stop)
    {
        sequence++;
        if (get_time_ms(&request_start_ms) == -1)
        {
            exit_status = 1;
            break;
        }
        result = process_one_ping(ctxt, identifier, sequence, &stats,
                                  request_start_ms); // TODO
        if (result == 1)
            break;
        if (result == -1)
        {
            exit_status = 1;
            break;
        }
        if (wait_unitl_next_send(request_start_ms) == -1) // TODO
        {
            exit_status = 1;
            break;
        }
    }
    print_stats(ctxt, &stats); // TODO
    return (exit_status);
}