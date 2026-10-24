/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:30:21 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/01/10 14:19:21 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**	SYNOPSIS: compare two strings
**
**	DESCRIPTION:
** 	The strcmp() function compares the two strings 's1' and 's2'.
**	The comparison is done using unsigned characters.
**
**	RETURN VALUE:
**	An integer less than, equal to, or greater than zero if the characters
**	of 's1' is found, respectively, to be less than, to match, or be greater
**	than 's2'.
*/

#include "../../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	i = 0;
	while ((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char *s1 = "This is 23";
//  	char *s2 = "This is 24";	

// 	printf("strcmp: %i\n", strcmp(s1, s2));
// 	printf("ft_strcmp: %i\n", ft_strcmp(s1, s2));
// }
