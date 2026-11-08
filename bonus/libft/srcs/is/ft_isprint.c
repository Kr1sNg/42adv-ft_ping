/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:58:35 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:51:57 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: ctype.h
**	SYNOPSIS: character classification functions
**
**	DESCRIPTION:
** 	checks for any printable character including space.
**
**	RETURN VALUE:
**	The values returned are nonzero if the character 'c' falls into the tested
**	class, and zero (0) if not.
*/

#include "../../includes/libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	int	c = 92;
	printf("%c\n", c);
	printf("isprint: %i\n", isprint(c));
	printf("ft_isprint: %i\n", ft_isprint(c));
	return (0);
}
*/
