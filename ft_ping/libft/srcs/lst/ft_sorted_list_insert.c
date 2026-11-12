/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorted_list_insert.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:42:22 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/17 16:28:41 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  LIBRARY: N/A
**  SYNOPSIS: create a new element and insert it into a list sorted
**	so that it remains sorted in ascending order.
**
**  RETURN VALUE: N/A
*/

#include "../../includes/libft.h"

// void	ft_list_sort(t_list **begin_list, int (*cmp)())
// {
// 	t_list	*curr;
// 	void	*temp;
// 	int		onoff;

// 	if (*begin_list == NULL)
// 		return ;
// 	onoff = 0;
// 	while (onoff == 0)
// 	{
// 		onoff = 1;
// 		curr = *begin_list;
// 		while (curr->next != NULL)
// 		{
// 			if (cmp(curr->data, curr->next->data) > 0)
// 			{
// 				temp = curr->data;
// 				curr->data = curr->next->data;
// 				curr->next->data = temp;
// 				onoff = 0;
// 			}
// 			curr = curr->next;
// 		}
// 	}
// }

void	ft_sorted_list_insert(t_list **begin_list, void *data, int (*cmp)())
{
	ft_list_push_front(begin_list, data);
	ft_list_sort(begin_list, cmp);
}

/*
static int	ft_cmp_int(void *d1, void *d2)
{
	return (*(int *)d1 - *(int *)d2);
}

#include <stdio.h>
static void	ft_printf_list(t_list *begin)
{
	while (begin != NULL)
	{
		printf("%i, ", *(int *)(begin->data));
		begin = begin->next;
	}
	printf("\n");
}

int	main(void)
{
	t_list *list = NULL;
	int a = 42, b = 113, c = -17, d = 8, e = -1000, f = 0;
	int	h = 9999;

    ft_list_push_front(&list, &f);
    ft_list_push_front(&list, &e);
    ft_list_push_front(&list, &d);
    ft_list_push_front(&list, &c);
    ft_list_push_front(&list, &b);
    ft_list_push_front(&list, &a);
	printf("Original: ");
    ft_printf_list(list);
	
	ft_sorted_list_insert(&list, &h, ft_cmp_int);
	printf("Insert Sorted: ");
	ft_printf_list(list);

	ft_list_clear(list);
	return (0);
}
*/