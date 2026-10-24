/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:36 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 11:57:33 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: remove one node from a linked list
**
**	DESCRIPTION:
** 	Takes as a parameter a node and frees the memory of the node's data 
**  using the function 'del' given as a parameter and free the node. The memory
**  of 'next' must not be freed.
**
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	if (del)
		del(lst->data);
	free(lst);
}
