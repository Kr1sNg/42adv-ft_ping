/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:36:14 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:59:11 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**	SYNOPSIS: compare memory areas
**
**	DESCRIPTION:
** 	The memcmp() function compares the first 'n' bytes (each interpreted as
**	unsigned char) of the memory areas 's1' and 's2'
**
**	RETURN VALUE:
**	An integer less than, equal to, or greater than zero if the first 'n' bytes
**	of 's1' is found, respectively, to be less than, to match, or be greater
**	than the first 'n' bytes of 's2'.
*/

#include "../../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((const unsigned char *)s1)[i] != ((const unsigned char *)s2)[i])
			return (((const unsigned char *)s1)[i]
											- ((const unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char *s1 = "this is ";
	char *s2 = "this is'\0'"; 	

	printf("memcmp: %i\n", memcmp(s1, s2, 7));
	printf("ft_memcmp: %i\n", ft_memcmp(s1, s2, 7));
}
*/