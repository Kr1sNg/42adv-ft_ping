/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:07:39 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:42:13 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: convert uppercase to lowercase
**
**	DESCRIPTION:
** 	If 'c' is an uppercase letter, tolower() returns its lowercase equivalent,
**	if a lowercase representation exists in the current locale. Otherwise, it
**	returns 'c'.
**
**	RETURN VALUE:
**	The value returned is that of the converted letter, or 'c' if the
**	conversion was not possible.
*/

#include "../../includes/libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	else
		return (c);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	char c = 'Z';
	printf("%c tolower: %c\n", c, tolower(c));
	printf("%c ft_tolower: %c\n", c, ft_tolower(c));
	return (0);
}
*/
