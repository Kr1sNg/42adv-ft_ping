/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:53:49 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:48:09 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: character classification functions
**
**	DESCRIPTION:
** 	checks for an alphanumeric character;
**	it is equivalent to (isalpha(c) || isdigit(c))
**
**	RETURN VALUE:
**	The values returned are nonzero if the character 'c' falls into the tested
**	class, and zero (0) if not.
*/

#include "../../includes/libft.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int c = '?';
	printf("isalnum: %i\n", isalnum(c));
	printf("ft_isalnum: %i\n", ft_isalnum(c));
	return (0);
}
*/
