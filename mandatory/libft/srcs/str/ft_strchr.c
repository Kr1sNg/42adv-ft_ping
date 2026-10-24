/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:29:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:13:36 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: locate character in string
**
**	DESCRIPTION:
** 	The strchr() function returns a pointer to the first occurrence of the
**	character 'c' in the string 's'.
**
**	RETURN VALUE:
**	a pointer to the matched character or NULL if the character is not found.
*/

#include "../../includes/libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while ((unsigned char)str[i] != '\0')
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)(str + i));
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(str + i));
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char *s = "tripouille";
	//int	c = '9';
	printf("strchr: %s.\n", strchr(s, 't' + 256));
	printf("ft_strchr: %s.\n", ft_strchr(s, 't' + 256));
	return (0);
}
*/
