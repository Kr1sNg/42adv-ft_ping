/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:35:19 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:42:15 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: extract substring from string.
**
**	DESCRIPTION:
** 	Allocates (with malloc()) and returns a substring from the string 's'.
** 	Substring begins at index (not char) 'start' and is of maximum size 'len'.
**
**	RETURN VALUE:
**	The substring. Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	slen;
	char	*sub;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		return (ft_strdup(""));
	if (len > slen - start)
		len = slen - start;
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	//char *s = "lorem ipsum dolor sit amet";
	//unsigned int start = 29;
	//unsigned int len = 10;
	char *sub = ft_substr("tripouille", 100, 1);
	printf("ft_substr: %s|\n", sub);
	printf("%i\n", strcmp(sub, ""));
	free(sub);

	return (0);
}
*/