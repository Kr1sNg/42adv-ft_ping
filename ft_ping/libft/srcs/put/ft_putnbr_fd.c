/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:05:40 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 11:59:35 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: write a number to the given file
**
**	DESCRIPTION:
** 	Outputs the integer 'n' to the given file descriptor.
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(fd, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		ft_putnbr_fd(nb / 10, fd);
	c = (nb % 10) + '0';
	write(fd, &c, 1);
}

/*
int main(void)
{
    ft_putnbr_fd(2147483647, 1);
    write(1, "\n", 1);
    ft_putnbr_fd(-2147483648, 1);
    write(1, "\n", 1);
    return 0;
}
*/