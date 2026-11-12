/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 07:29:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:38:57 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: locate character in string
**
**	DESCRIPTION:
** 	The strchr() function returns a pointer to the last occurrence of the
**	character 'c' in the string 's'.
**
**	RETURN VALUE:
**	a pointer to the matched character or NULL if the character is not found.
*/

#include "../../includes/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	count;

	i = 0;
	count = -1;
	while ((unsigned char)str[i] != '\0')
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			count = i;
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(str + i));
	else if (count != -1)
		return ((char *)(str + count));
	else
		return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	const char *str = "tripouille";
	//int	c = (char)'.';
	printf("strrchr: %s.\n", strrchr(str, 't' + 256));
	printf("ft_strrchr: %s.\n", ft_strrchr(str, 't' + 256));
	return (0);
}
*/
