/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 11:43:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:23:40 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: <bsd/string.h> (libbsd, -lbsd)
**
**	SYNOPSIS: size-bounded string concatenation
**
**	DESCRIPTION:
** 	The strlcat() function appends the NUL-terminated string 'src' to
**	the end of 'dst'. It will append at most (size - strlen(dst) - 1) bytes,
**	NUL-terminating the result.
**
**	RETURN VALUE:
**	the total length of the string it tried to create.
**	return length of (src + dest) or (src + size (if size < dest))
*/

#include "../../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	s_len = ft_strlen(src);
	d_len = ft_strlen(dst);
	if (size < d_len)
		return (size + s_len);
	i = 0;
	while (src[i] != '\0' && (d_len + i < size - 1) && size > 0)
	{
		dst[d_len + i] = src[i];
		i++;
	}
	dst[d_len + i] = '\0';
	return (d_len + s_len);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	unsigned int	s = -1; 
	//char	*src = (char *)"AAAAAAAAA";
	//char	dst1[30];
	char	dst2[30];

	//printf("len_dst1: %lu, len_dst2: %lu\n", ft_len(dst1), ft_len(dst2));
	//printf("strlcat: %lu, dst: %s\n", strlcat(dst1, "123", s), dst1);
	printf("ft_strlcat: %lu, dst: %s\n", ft_strlcat(dst2, "AAAAAA", s), dst2);
	return (0);
}
*/