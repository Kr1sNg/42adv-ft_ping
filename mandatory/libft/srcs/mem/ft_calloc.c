/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:20:54 by tat-nguy          #+#    #+#             */
/*   Updated: 2024/12/02 18:45:31 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: stdlib.h
**	SYNOPSIS: allocate dynamic memory by zero
**
**	DESCRIPTION:
** 	The  calloc()  function allocates memory for an array of 'nmemb' elements
**	of 'size' bytes each and returns a pointer to the allocated memory.
**	The memory is set to zero. If 'nmemb' or 'size' is 0, then calloc() returns
**	either NULL, or a unique pointer value that can later be successfully
**	passed to free(). If the multiplication of 'nmemb' and 'size' would result
**	in integer overflow, then calloc() returns an error. By contrast, an
**	integer overflow would not be detected in the following call to malloc(),
**	with the result that an incorrectly sized block of memory would be
**	allocated: malloc(nmemb * size);
**
**	RETURN VALUE:
**	A pointer to the allocated memory, which is suitably aligned for any
**	built-in type, or NULL if the request failed.
*/

#include "../../includes/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*s;
	size_t	total_size;
	size_t	i;

	total_size = nmemb * size;
	s = malloc(total_size);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((char *)s)[i] = 0;
		i++;
	}
	return (s);
}

/*
#include <stdio.h>
int	main(void)
{
	int *array = ft_calloc(4, sizeof(int));
	int i = 0;
	while (i < 4)
	{
		printf("%i", array[i]);
		i++;
	}
	free(array);
}
*/