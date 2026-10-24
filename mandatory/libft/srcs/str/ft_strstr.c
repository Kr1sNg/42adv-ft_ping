/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:32:37 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/09/24 19:26:10 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: locate a substring in a string
**
**	DESCRIPTION:
** 	The  strstr() function finds the first occurrence of the substring 'to_find'
**	in the string 'str'. The terminating null bytes ('\0') are not compared.
**	
**	RETURN VALUE:
**	A pointer to the beginning of the located sub‐string,
**	or NULL if the substring is not found.
*/

#include "../../includes/libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int	s;
	int	i;

	s = 0;
	i = 0;
	if (to_find[0] == '\0')
		return (str);
	while (str[s] != '\0')
	{
		while (str[s + i] == to_find[i] && str[s + i] != '\0')
		{
			i++;
		}
		if (to_find[i] == '\0')
			return (str + s);
		s++;
		i = 0;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char str[] = "Bonjour et bienvenu dans ce jeu tant attendu..";
	char to_find[] = "venu";

	printf("real: %s\n", strstr(str, to_find));
	printf("fake: %s\n", ft_strstr(str, to_find));
}
*/