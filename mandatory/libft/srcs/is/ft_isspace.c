/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 18:52:46 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:53:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: character classification functions
**
**	DESCRIPTION:
** 	checks for white-space characters.  In the "C" and "POSIX" locales,
**	these are: space (' '), form-feed ('\f'), newline ('\n'),
**	carriage return ('\r'), horizontal tab ('\t'), and vertical tab ('\v').
**
**	RETURN VALUE:
**	The values returned are nonzero if the character 'c' falls into the tested
**	class, and zero (0) if not.
*/

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\f' || c == '\n' || c == '\r'
		|| c == '\t' || c == '\v')
		return (8192);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>
int	main(void)
{
	printf("isspace: %i\n", isspace('a'));
	printf("ft_isspace: %i\n", ft_isspace('a'));
}
*/
