/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:15:16 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 21:20:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/*
** :::::::::::::::::::::::::::::::::* HEADERS *:::::::::::::::::::::::::::::: **
*/

# include <stdarg.h>
# include "libft.h"

/*
** ::::::::::::::::::::::::::* FUNCTION PROTOTYPES *::::::::::::::::::::::::: **
*/

int		ft_printf(const char *mand_arg, ...);
int		ft_print_format(char c, va_list ap);
int		ft_print_char(int c);
int		ft_print_str(char *str);
int		ft_print_dec(long n);
int		ft_print_hex(unsigned long long n, char c);
int		ft_print_ptr(unsigned long long p);

#endif