/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:56:40 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 12:01:32 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: remove unwanted characters at the beginning and the end of string
**
**	DESCRIPTION:
** 	Allocates (with malloc(3)) and returns a copy of 's1' with the characters
**	specified in 'set' removed from the beginning and the end of the string.
**
**	RETURN VALUE:
**	The trimmed string. Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	i;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, s1[i]) != NULL)
		i++;
	s1 = &s1[i];
	len = ft_strlen(s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]) != NULL)
		len--;
	trimmed = ft_substr(s1, 0, len);
	return (trimmed);
}

/*
#include <stdio.h>
int main(void)
{
	char s1[] = "  Today is Monday, ";
	char set[] = ", Today";
	char *new = ft_strtrim(s1, set);
	printf("ft_strtrim: _%s_\n", new);
	free(new);
	return (0);
}
*/