/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:02:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 12:01:12 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: create new string from modifying string with specified function
**
**	DESCRIPTION:
** 	Applies the function 'f' to each character of the string 's', passing its
**	index as the first argument and the character itself as the second.
**	A new string is created (using malloc(3)) to collect the results from the
**	successive applications of 'f'.
**
**	RETURN VALUE:
**	The string created from the successive applications of 'f'.
**	Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	if (!s || !f)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
#include <stdio.h>
// Convert character to uppercase if index is even, lowercase if odd
char	ft_toupper_even(unsigned int i, char c)
{
	if (i % 2 == 0)
	{
		if (c >= 'a' && c <= 'z')
			return (c - ('a' - 'A'));
	}
	else
	{
		if (c >= 'A' && c <= 'Z')
			return (c + ('a' - 'A'));
	}
	return (c);
}

int main(void)
{
	char	*s = "This is CS 50 from Harvard University.";
	char	*t = ft_strmapi(s, &ft_toupper_even);

	printf("ft_strmapi: %s\n", t);
	free(t);
	return (0);
}
*/
