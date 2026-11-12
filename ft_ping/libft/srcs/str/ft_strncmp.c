/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:30:21 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 13:45:22 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**	SYNOPSIS: compare two strings
**
**	DESCRIPTION:
** 	The strncmp() function compares only the first (at most) 'n' bytes the two
**	strings 's1' and 's2'. The comparison is done using unsigned characters.
**
**	RETURN VALUE:
**	An integer less than, equal to, or greater than zero if the first 'n' bytes
**	of 's1' is found, respectively, to be less than, to match, or be greater
**	than 's2'.
*/

#include "../../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while (((unsigned char)s1[i] != '\0' || (unsigned char)s2[i] != '\0')
		&& i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char *s1 = "<ba";
 	char *s2 = "<a";	

	// printf("strncmp: %i\n", strncmp(s1, s2, -1));
	printf("ft_strncmp: %i\n", ft_strncmp(s1, s2, -1));
}
*/