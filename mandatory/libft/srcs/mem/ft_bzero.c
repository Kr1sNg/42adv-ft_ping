/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:26:29 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:32:58 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: strings.h
**	SYNOPSIS: zero a byte string
**
**	DESCRIPTION:
** 	The  bzero() function erases the data in the 'n' bytes of the memory
**	starting at the location pointed to by 's', by writing zeros (bytes 
**	containing '\0') to that area.
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = '\0';
		i++;
	}
}

/*
#include <stdio.h>
#include <strings.h>
int	main(void)
{
	unsigned int i = 0;
	unsigned int n = 4;
	char s1[20] = "This is 42 Perpignan";
	bzero(s1, n);
	printf("bzero: ");
	while (i < 19)
	{
		if (s1[i] == '\0')
			printf(".");
		else
			printf("%c", s1[i]);
		i++;
	}
	printf("\n");

	i = 0;
	char s2[20] = "This is 42 Perpignan";
	ft_bzero(s2, n);
	printf("ft_bzero: ");
	while (i < 19)
	{
		if (s2[i] == '\0')
			printf("/");
		else
			printf("%c", s2[i]);
		i++;
	}
	printf("\n");
}
*/