/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:45:44 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/13 15:29:58 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: write a string (followed by a newline) to the standard output
**
**	DESCRIPTION:
** 	Outputs the string 's' to the standard output followed by a newline.
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_putendl(char *s)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
	write(1, "\n", 1);
}
