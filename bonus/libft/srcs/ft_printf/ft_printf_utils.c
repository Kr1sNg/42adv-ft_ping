/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:37:03 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 22:04:53 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int		i;

	if (str == NULL)
		return (ft_print_str("(null)"));
	i = 0;
	while (str[i] != '\0')
	{
		write (1, &str[i++], 1);
	}
	return (i);
}

int	ft_print_dec(long n)
{
	char	c;
	int		count;

	count = 0;
	if (n < 0)
	{
		count += write(1, "-", 1);
		n = -n;
	}
	if (n >= 10)
	{
		count += ft_print_dec(n / 10);
		count += ft_print_dec(n % 10);
	}
	else
	{
		c = n + '0';
		count += ft_print_char(c);
	}
	return (count);
}

int	ft_print_hex(unsigned long long n, char c)
{
	int		count;

	count = 0;
	if (n >= 16)
	{
		count += ft_print_hex(n / 16, c);
		count += ft_print_hex(n % 16, c);
	}
	else
	{
		if (c == 'x')
			count += ft_print_char("0123456789abcdef"[n]);
		if (c == 'X')
			count += ft_print_char("0123456789ABCDEF"[n]);
	}
	return (count);
}

int	ft_print_ptr(unsigned long long p)
{
	int		count;

	count = 0;
	if (!p)
		count += ft_print_str("(nil)");
	else
	{
		count += ft_print_str("0x");
		count += ft_print_hex(p, 'x');
	}
	return (count);
}
