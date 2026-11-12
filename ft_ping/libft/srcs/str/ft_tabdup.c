/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:20:40 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/14 12:56:06 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	**ft_tabdup(char **tab)
{
	int		i;
	int		len;
	char	**dest;

	if (!tab)
		return (NULL);
	i = 0;
	len = ft_tablen(tab);
	dest = ft_calloc((len + 1), sizeof(char *));
	if (!dest)
		return (NULL);
	while (tab[i])
	{
		dest[i] = ft_strdup(tab[i]);
		i++;
	}
	return (dest);
}
