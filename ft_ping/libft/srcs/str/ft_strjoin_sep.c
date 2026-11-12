/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:45:13 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/03/14 13:39:55 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	NOTICE: Need to free() after using
**	LIBRARY: N/A
**	SYNOPSIS: concatenate all strings pointed by 'strs' into a new string
** 	which is separated by a 'sep' string.
**
**	DESCRIPTION:
** 	Allocates (with malloc(3)) and returns a new string, which is the result
**	of the concatenation all strings pointed by 'strs'.
**
**	RETURN VALUE:
**	The new string. Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

static int	ft_lenstrs(int size, char **strs, char *sep)
{
	int	i;
	int	length;

	i = 0;
	length = 0;
	if (!strs || !size)
		return (0);
	while (i < size)
	{
		length = length + ft_strlen(strs[i]);
		i++;
	}
	length = length + ft_strlen(sep) * (size - 1);
	return (length);
}

char	*ft_strjoin_sep(char **strs, char *sep)
{
	char	*strfinal;
	int		n;
	int		size;

	if (!strs || !ft_tablen(strs))
		return (NULL);
	size = ft_tablen(strs);
	strfinal = ft_calloc(ft_lenstrs(size, strs, sep) + 1, sizeof(char));
	if (!strfinal)
		return (0);
	n = 0;
	while (n < size)
	{
		ft_strcat(strfinal, strs[n]);
		if (n < size - 1)
			ft_strcat(strfinal, sep);
		n++;
	}
	return (strfinal);
}

// #include <stdio.h>
// int main()
// {
// 	char *s = "***hello***hi***salut***this***is****a***coucou****";
//     char    **strs = ft_split_charset(s, "*");
//     char    *sep = "*";
//     char    *new = ft_strjoin_sep(strs, sep);
//     printf("%s\n", new);
//     free(new);
// 	ft_split_free(strs);
// }
