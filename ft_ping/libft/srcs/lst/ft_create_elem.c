/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:24:42 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/10/07 19:17:01 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**  LIBRARY: N/A
**  SYNOPSIS: create new node with data
**
**  RETURN VALUE: new node
*/

#include <stdlib.h>
#include "../../includes/libft.h"

t_list	*ft_create_elem(void *data)
{
	t_list	*new_elem;

	new_elem = (t_list *)malloc(sizeof(t_list));
	if (!new_elem)
		return (NULL);
	new_elem->next = NULL;
	new_elem->data = data;
	return (new_elem);
}

/*
#include <stdio.h>
int	main(void)
{
	int	value = 42;
// *element (or *new_elem) is a pointer to a structure of type t_list
	t_list	*element = ft_create_elem(&value);
	if (element == NULL)
	{
		printf("Memory allocation failed\n");
		return (1);
	}
//so to access the member, from a pointer, we have to use ->
// . is used only if element is an actual structure, not a pointer.
// and here we typecaste (void*) to (int*) of element to get value
	printf("Data: %i\n", *(int *)(element->data));
	if (element->next == NULL)
		printf("Next pointer is NULL\n");
	free(element);
	return (0);
}*/
