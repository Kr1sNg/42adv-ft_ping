/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 09:22:49 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 11:56:47 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: remove and free all the linked list
**  
**	DESCRIPTION:
** 	Deletes and frees the given node and every successor of that node, using
**  the function 'del' and free(3). Finally, the pointer to the list must be
**  set to NULL.
**    
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	while (*lst != NULL)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		if (del != NULL)
			del(tmp->data);
		free(tmp);
	}
	*lst = NULL;
}
