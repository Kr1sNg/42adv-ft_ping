/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:07:39 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:43:53 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: convert lowercase to uppercase
**
**	DESCRIPTION:
** 	If 'c' is a lowercase letter, toupper() returns its uppercase equivalent,
**	if an uppercase representation exists in the current locale. Otherwise, it
**	returns 'c'.
**
**	RETURN VALUE:
**	The value returned is that of the converted letter, or 'c' if the
**	conversion was not possible.
*/

#include "../../includes/libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	else
		return (c);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	char c = '?';
	printf("%c toupper: %c\n", c, toupper(c));
	printf("%c ft_toupper: %c\n", c, ft_toupper(c));
	return (0);
}
*/
