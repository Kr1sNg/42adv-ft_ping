/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:00:14 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 19:16:07 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: string.h
**
**	SYNOPSIS: copy a string
**
**	DESCRIPTION:
** 	The strcpy() function copies the string pointed to by 'src', including the
**  terminating 'null' byte ('\0'), to the buffer pointed to by 'dest'.
**  The strings may not overlap, and the destination string 'dest' must be
**  large enough to receive the copy.
**
**	RETURN VALUE:
**	a pointer to the destination string 'dest'
*/

char	*ft_strcpy(char *dest, char *src)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
