/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:21:55 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/11/09 11:57:46 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: N/A
**	SYNOPSIS: apply function to all the node of linked list
**  
**	DESCRIPTION:
** 	Iterates the list 'lst' and applies the function 'f' on the data of
**  each node.
**    
**	RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst != NULL)
	{
		f(lst->data);
		lst = lst->next;
	}
}
