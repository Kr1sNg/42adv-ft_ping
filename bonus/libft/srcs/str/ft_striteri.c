/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:36:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 12:02:38 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: modify string with specified function
**
**	DESCRIPTION:
** 	Applies the function 'f' on each character of the string 's' passed as
**	argument, passing its index as first argument. Each character is passed by
**	address to 'f' to be modified if necessary.
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>

void    iter(unsigned int i, char *c)
{
    static int indexArray[11] = {0};

    if (i > 10 || indexArray[i] == 1)
        write(1, "wrong index\n", 12);
    else
        indexArray[i] = 1;
    if (*c >= 'a' && *c <= 'z')
        *c = *c - 32;
    else if (*c >= 'A' && *c <= 'Z')
        *c = *c + 32;
}

int main(void)
{
	char	s[] = "This is";
	printf("ft_striteri before: %s\n", s);

	ft_striteri(s, &iter);
	printf("ft_striteri after: %s\n", s);
	return (0);
}
*/