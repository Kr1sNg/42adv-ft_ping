/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:27:59 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/13 23:47:57 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: calculate the length of a string
**
**	DESCRIPTION:
** 	The strlen() function calculates length of the string pointed to by 's',
**	excluding the terminating null byte ('\0').
**
**	RETURN VALUE:
**	The number of bytes in the string pointed to by 's'.
*/

#include "../../includes/libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
#include <stdio.h>
int	main(void)
{
	char *str = "This is 9";
	printf("strlen: %lu\n", strlen(str));
	printf("ft_strlen: %lu\n", ft_strlen(str));
	return (0);
}
*/
