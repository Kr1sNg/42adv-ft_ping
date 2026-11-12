/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_charset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 20:29:23 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/02/19 14:20:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	NOTICE: Need to use ft_split_free() after using
**
**	LIBRARY: N/A
**	SYNOPSIS: separate a string into substrings delimited by set of characters
**
**	DESCRIPTION:
** 	Allocates (with malloc) and returns an array of strings obtained by
**	splitting 's' using the set of character 'charset' as a delimiter.
**	The array must end with a NULL pointer.
**
**	RETURN VALUE:
**	The array of new strings resulting from the split.
**	Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

static size_t	check_charset(char c, char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	count_words(const char *str, char *charset)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
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

static size_t	count_letter(const char *str, char *charset)
{
	int	i;

	i = 0;
	while ((str[i] != '\0') && (check_charset(str[i], charset) == 0))
		i++;
	return (i);
}

static char	*ft_strdup_s(const char *src, char *charset)
{
	size_t	i;
	size_t	len;
	char	*arr;

	i = 0;
	len = count_letter(src, charset);
	arr = malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	while (i < len)
	{
		arr[i] = src[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	**ft_split_charset(char const *str, char *charset)
{
	size_t	i;
	size_t	j;
	char	**arrs;

	i = 0;
	j = 0;
	arrs = malloc(sizeof(char *) * (count_words(str, charset) + 1));
	if (!arrs)
		return (NULL);
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_charset(str[i], charset) == 1)
			i++;
		if (str[i] != '\0' && check_charset(str[i], charset) == 0)
		{
			arrs[j] = ft_strdup_s(str + i, charset);
			if (arrs[j] == NULL)
				return (ft_split_free(arrs), NULL);
			j++;
			while (str[i] != '\0' && check_charset(str[i], charset) == 0)
				i++;
		}
	}
	arrs[j] = NULL;
	return (arrs);
}

/*
#include <stdio.h>
int	main(void)
{
	char **arrs;
	char *str = " He=llo... The,New - = +  Future.e != ";
	char *charset = "  =,. ";
	int i = 0;
	arrs = ft_split_charset(str, charset);
	if (!arrs)
		return (1);
	while (arrs[i] != NULL)
	{
		printf("%s\n", arrs[i]);
		free(arrs[i]);
		i++;
	}
	free(arrs);
	return (0);
}
*/
