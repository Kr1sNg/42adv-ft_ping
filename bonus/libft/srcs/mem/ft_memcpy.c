/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:45:51 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:00:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**	SYNOPSIS: copy memory area
**
**	DESCRIPTION:
** 	The memcpy() function copies 'n' bytes (even 'null' characters) from memory 
**	area 'src' to memory area 'dest'. The memory areas must not overlap.
**
**	RETURN VALUE:
**	The memcpy() function returns a pointer to 'dest'
*/

#include "../../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}

/*
#include <string.h>
#include <stdio.h>
int main(void)
{
	char	src[] = "This is";
	char	dst1[] = "Ah voila";
	char	dst2[] = "Ah voila";

	printf("memcpy: %s\n", (char *)memcpy(dst1, src, 7));
	printf("ft_memcpy: %s\n", (char *)ft_memcpy(dst2, src, 7));
}
*/