/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:22:35 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:50:07 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: character classification functions
**
**	DESCRIPTION:
** 	checks whether 'c' is a 7-bit unsigned char value that fits into the ASCII
**	character set.
**
**	RETURN VALUE:
**	The values returned are nonzero if the character 'c' falls into the tested
**	class, and zero (0) if not.
*/

#include "../../includes/libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int c = 200;
	printf("isascii: %i\n", isascii(c));
	printf("ft_isascii: %i\n", ft_isascii(c));
	return (0);
}
*/
