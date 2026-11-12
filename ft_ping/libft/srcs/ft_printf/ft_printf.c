/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 14:33:47 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/14 21:20:45 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

int	ft_printf(const char *mand_arg, ...)
{
	int		i;
	int		count;
	va_list	ap;

	va_start(ap, mand_arg);
	i = 0;
	count = 0;
	while (mand_arg[i] != '\0')
	{
		if (mand_arg[i] == '%')
		{
			i++;
			count += ft_print_format(mand_arg[i], ap);
		}
		else
			count += write(1, &mand_arg[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}

int	ft_print_format(char c, va_list ap)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		count += ft_print_ptr((unsigned long long)va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		count += ft_print_dec((long)va_arg(ap, int));
	else if (c == 'u')
		count += ft_print_dec((long)va_arg(ap, unsigned int));
	else if (c == 'x' || c == 'X')
		count += ft_print_hex((unsigned long long)va_arg(ap, unsigned int), c);
	else if (c == '%')
		count += ft_print_char('%');
	return (count);
}
