/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 08:43:06 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 11:58:24 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: create new node for a linked list
**
**	DESCRIPTION:
** 	Allocates (with malloc(3)) and returns a new node. The member variable
**  'data' is initialized with the value of the parameter 'data'.
**  The variable 'next' is initialized to NULL.
**
**	RETURN VALUE:
**	The new node.
**	Or NULL if the allocation fails.
*/

#include "../../includes/libft.h"

t_list	*ft_lstnew(void *data)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->data = data;
	node->next = NULL;
	return (node);
}
