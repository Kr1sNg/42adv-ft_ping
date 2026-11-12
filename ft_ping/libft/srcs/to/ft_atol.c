/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:04:40 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/01/09 16:09:15 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: stdlib.h
**	SYNOPSIS: convert string into long int.
**
**	DESCRIPTION:
** 	The atol() function converts the initial portion of the string pointed to
**	by 'nptr' to long int.
**
**	RETURN VALUE:
**	The converted value or 0 on error. 
*/

#include "../../includes/libft.h"

long	ft_atol(const char *s)
{
	int		i;
	long	l;
	int		sign;

	i = 0;
	l = 0;
	sign = 1;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		l = l * 10 + (s[i] - '0');
		i++;
	}
	return (l * sign);
}

/*
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char **argv)
{
	if (argc != 2)
		return (-42);
	ft_printf("atol: %i\n", atoi(argv[1]));
	ft_printf("ft_atol: %i\n", ft_atoi(argv[1]));
}
*/