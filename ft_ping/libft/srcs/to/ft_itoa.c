/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 10:39:33 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/20 13:35:10 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: transform int into string
**
**	DESCRIPTION:
** 	Allocates (with malloc(3)) and returns a string representing the integer
**	received as an argument. Negative numbers must be handled.
**
**	RETURN VALUE:
**	The string representing the integer.
**	Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

static int	ft_ilen(long n)
{
	int		count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

static	void	recursive(long nb, char *str, int *i)
{
	if (nb >= 10)
		recursive(nb / 10, str, i);
	str[(*i)++] = (nb % 10) + '0';
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	long	nb;
	char	*str;

	nb = n;
	len = ft_ilen(nb);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (nb < 0)
	{
		str[i] = '-';
		nb = -nb;
		i++;
	}
	recursive(nb, str, &i);
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>
int main(void)
{
    char *abc;
           abc = ft_itoa(-2147483648);
       printf("%s\n", abc);
       free(abc);
}
*/
