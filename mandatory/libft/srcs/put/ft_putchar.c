/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:16:26 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:05:24 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: write a character to the standard output
**
**	DESCRIPTION:
** 	Outputs the character 'c' to the the standard output
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_putchar(int c)
{
	write(1, &c, 1);
}
