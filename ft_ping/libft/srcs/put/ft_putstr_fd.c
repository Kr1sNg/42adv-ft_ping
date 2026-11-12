/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:44:51 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 11:59:41 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: write a string to the given file
**
**	DESCRIPTION:
** 	Outputs the string 's' to the given file descriptor.
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}

/*
#include <fcntl.h>
int main(void)
{
    // Example 1: Writing to standard output (fd = 1)
    ft_putstr_fd("Hello, standard output!", 1);

    // Example 2: Writing to a file
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        // Handle file open error
        write(2, "Error opening file.\n", 20);
        return (1);
    }

    ft_putstr_fd("Hello, file!", fd);

    // Close the file descriptor after use
    close(fd);

    return 0;
}
*/