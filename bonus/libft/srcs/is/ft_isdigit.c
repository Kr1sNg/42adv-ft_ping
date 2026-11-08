/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:55:31 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:50:54 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: character classification functions
**
**	DESCRIPTION:
** 	checks for a digit (0 through 9)
**
**	RETURN VALUE:
**	The values returned are nonzero if the character 'c' falls into the tested
**	class, and zero (0) if not.
*/

#include "../../includes/libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (2048);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int c = ':';

	printf("isdigit: %i\n", isdigit(c));
	printf("ft_isdigit: %i\n", ft_isdigit(c));

	return (0);
}
*/
