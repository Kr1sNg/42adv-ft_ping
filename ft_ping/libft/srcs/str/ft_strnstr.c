/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:38 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:37:42 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: <bsd/string.h> (libbsd, -lbsd)
**
**	SYNOPSIS: locate a substring in a string
**
**	DESCRIPTION:
** 	The strnstr() function locates the first occurrence of the null-terminated
**	string 'little' in the string 'big', where not more than len characters are
**	searched. Characters that appear after a ‘\0’ character are not searched.
**	
**	RETURN VALUE:
**	If 'little' is an empty string, 'big' is returned;
**	if 'little' occurs nowhere in 'big', NULL is returned;
**	or a pointer to first char of first occurrence of 'little' is returned.
*/

#include "../../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	if (little[0] == '\0')
		return ((char *)big);
	if (len == 0)
		return (0);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while ((i + j < len) && big[i + j] != '\0' && little[j] == big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		i++;
	}
	return (0);
}

/*
#include <bsd/string.h>
#include <stdio.h>
int	main(void)
{
	char big[] = "Visual Studio Code with GitHub Copilot supercharges your code";
	char little[] = "with";
	printf("strnstr: %s\n", strnstr(big, little, 0));
	printf("ft_strnstr: %s\n", ft_strnstr(big, little, 0));
}
*/