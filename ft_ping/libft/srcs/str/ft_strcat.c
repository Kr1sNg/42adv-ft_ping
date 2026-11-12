/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:05:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:11:27 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: concatenate two strings
**
**	DESCRIPTION:
** 	The strcat() function appends the 'src' string to the 'dest' string,
**  overwriting the old terminating 'null' byte ('\0') of 'dest', and then
**  adds another terminating 'null' byte at the end. The strings may not
**  overlap, and the 'dest' string must have enough space for the result.
**
**	RETURN VALUE:
**	a pointer to the resulting string 'dest'.
*/

#include "../../includes/libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	unsigned int	i;
	unsigned int	d_len;

	d_len = ft_strlen(dest);
	i = 0;
	while (src[i] != '\0')
	{
		dest[d_len + i] = src[i];
		i++;
	}
	dest[d_len + i] = '\0';
	return (dest);
}
