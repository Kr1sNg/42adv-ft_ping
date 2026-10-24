/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:31:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:03:14 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**	SYNOPSIS: copy memory area
**
**	DESCRIPTION:
** 	The memmove() function copies 'n' bytes from memory area 'src' to memory
**	area 'dest'. The memory areas may overlap (src + n > dest): copying from
**	the end of the 'src' back to the beginning.
**
**	RETURN VALUE:
**	a pointer to 'dest'
*/

#include "../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	if (dest > src && src + n > dest)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return (dest);
}

/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	
	char	src1[] = "this_is_9";
	char	*dst1 = NULL;
	printf("dst1: %s.\n", dst1);
	printf("memmove: %s.\n", (char *)memmove(dst1, src1, 5));

	char	src2[] = "THIS_IS_9";
	char	*dst2 = NULL;
	printf("dst2: %s.\n", dst2);
	printf("ft_memmove: %s.\n", (char *)ft_memmove(dst2, src2, 5));
}
*/
