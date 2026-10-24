/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 17:40:40 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:04:38 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**	SYNOPSIS: fill memory with a constant byte
**
**	DESCRIPTION:
** 	The memset() function fills the first 'n' bytes of the memory area pointed
**	to by 's' with the constant byte 'c'.
**
**	RETURN VALUE:
**	The memset() function returns a pointer to the memory area 's'
*/

#include "../../includes/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = c;
		i++;
	}
	return (s);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	s1[] = "Welcome to New York!";
	char	s2[] = "Welcome to New York!";
	int		c = '#';
	unsigned n = 4;

	printf("   memset: %s\n", (char *)memset(s1, c, n));
	printf("ft_memset: %s\n", (char *)ft_memset(s2, c, n));
}
*/