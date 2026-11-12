/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 21:31:41 by tat-nguy          #+#    #+#             */
/*   Updated: 2025/01/08 21:55:12 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	NOTICE: Need to use ft_split_free() after using ft_split()
**
**	LIBRARY: N/A
**	SYNOPSIS: free all allocated memory after using function splits
**
*/

#include "../../includes/libft.h"

void	ft_split_free(char **arrs)
{
	size_t	i;

	i = 0;
	if (!arrs)
		return ;
	while (arrs[i] != NULL)
	{
		free(arrs[i]);
		i++;
	}
	free(arrs);
}
