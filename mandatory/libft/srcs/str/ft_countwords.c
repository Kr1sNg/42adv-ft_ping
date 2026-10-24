/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countwords.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:29:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 13:20:08 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**
**	LIBRARY: N/A
**	SYNOPSIS: count word numbers in a string separeted by a charset collection
**
**	RETURN VALUE:
**	Number of words in string.
**	
*/

#include "../../includes/libft.h"

static size_t	check_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	if (!charset)
		return (0);
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_countwords(const char *str, char *charset)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		while ((str[i] != '\0') && (check_charset(str[i], charset) == 1))
			i++;
		if ((str[i] != '\0') && (check_charset(str[i], charset) == 0))
		{
			count++;
			while (str[i] != '\0' && check_charset(str[i], charset) == 0)
				i++;
		}
	}
	return (count);
}

// #include <stdio.h>
// int	main(void)
// {
// 	char *str = " Hello * this is ***4*** ";
// 	char *charset = "";
// 	int i = ft_countwords(str, charset);
// 	printf("words: %i\n", i);
// 	return (0);
// }