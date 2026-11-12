/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:45:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 13:37:59 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: concatenate 2 strings into a new string.
**
**	DESCRIPTION:
** 	Allocates (with malloc(3)) and returns a new string, which is the result
**	of the concatenation of 's1' then 's2'.
**
**	RETURN VALUE:
**	The new string. Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

	// static char	*ft_strcat(char *dest, const char *src)
	// {
	// 	size_t	i;
	// 	size_t	d_len;

	// 	d_len = ft_strlen(dest);
	// 	i = 0;
	// 	while (src[i] != '\0')
	// 	{
	// 		dest[d_len + i] = src[i];
	// 		i++;
	// 	}
	// 	dest[d_len + i] = '\0';
	// 	return (dest);
	// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	lens1;
	size_t	lens2;
	char	*new;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	new = malloc(sizeof(char) * (lens1 + lens2 + 1));
	if (!new)
		return (NULL);
	new[0] = '\0';
	ft_strcat(new, s1);
	ft_strcat(new, s2);
	return (new);
}

/*
#include <stdio.h>
int main(void)
{
	char s1[] = "Today is Monday, ";
	char s2[] = "it's a beautiful day.";
	char *new = ft_strjoin(s1, s2);
	printf("ft_strjoin: %s\n", new);
	free(new);
}
*/