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
**	LIBRARY:
**	SYNOPSIS: string classification functions
**
**	DESCRIPTION:
** 	checks for a digit (0 through 9) in a string
**
**	RETURN VALUE:
**	The values returned are nonzero if the string 's' falls into the tested
**	class, and zero (0) if not.
*/

#include "../../includes/libft.h"

int	ft_isdigit_s(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

/*
#include <ctype.h>
#include <stdio.h>

int	main(void)
{
	char *s = "01 2";

	printf("ft_isdigit_s: %i\n", ft_isdigit_s(s));

	return (0);
}
*/