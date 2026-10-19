/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/19 16:46:59 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/19 22:38:20 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

typedef struct s_ping_option
{
    bool verbose;
    const char *dest;
} t_ping_option;

void print_help(const char *prog_name);
void print_error(const char *prog_name);
int parse_args(int ac, char **av, t_ping_option *op);

#endif