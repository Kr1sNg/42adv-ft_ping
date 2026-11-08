/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_list_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:21 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/31 11:54:03 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  LIBRARY: N/A
**  SYNOPSIS: find the first element which has the data compared to 'data_ref'
**	with 'cmp' makes 'cmp' to return 0.
**
**  RETURN VALUE:
**	the address of the first found element
*/

#include "../../includes/libft.h"

t_list	*ft_list_find(t_list *begin_list, void *data_ref,
			int (*cmp)(void *, void *))
{
	t_list	*curr;

	curr = begin_list;
	while (curr != NULL)
	{
		if (cmp(curr->data, data_ref) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

/*
int	ft_int_compare(void *data, void *ref)
{
	int *a = (int *)data;
	int *b = (int *)ref;

	return (*a - *b);
}

void	ft_list_push_front(t_list **begin_list, void *data)
{
	t_list *new;
	
	new = ft_create_elem(data);
	if (new != NULL)
	{
		new->next = *begin_list;
		*begin_list = new;
	}
}

void	ft_list_clear(t_list *begin_list)
{
	t_list	*temp;

	while (begin_list != NULL)
	{
		temp = begin_list;
		begin_list = begin_list->next;
		free(temp);
	}
}

#include <stdio.h>
int	main(void)
{
	int	a = 42;
	int b = 66;
	int c = 34;
	int ref = 67;
	t_list *list = NULL; //REMEMBER to set list = NULL
	t_list *result;

	ft_list_push_front(&list, &a);
	ft_list_push_front(&list, &b);
	ft_list_push_front(&list, &c);

	result = ft_list_find(list, &ref, ft_int_compare);
	
	if (result != NULL)
		printf("%i\n", *(int *)(result->data));
	else
		printf("NULL!\n");

	ft_list_clear(list);
}
*/
