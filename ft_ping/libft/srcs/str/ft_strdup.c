/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:39:27 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/15 12:32:00 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: duplicate a string
**
**	DESCRIPTION:
** 	The strdup() function returns a pointer to a new string which is a
**	duplicate of the string 's'. Memory for the new string is obtained with
**	malloc(), and can be freed with free().
**
**	RETURN VALUE:
**	On success, the strdup() function returns a pointer to the duplicated string.
**	It returns NULL if insufficient memory was available.
*/

#include "../../includes/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dup;

	if (!s || !s[0])
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char *s = "This is 42 Perpignan.";
	char *dup1 = strdup(s);
	char *dup2 = ft_strdup(s);
	printf("strdup: %s\n", dup1);
	printf("ft_strdup: %s\n", dup2);
	free(dup1);
	free(dup2);
	return (0);
}
*/