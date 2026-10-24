/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:20:21 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 11:56:59 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

/*
**	LIBRARY: math.h
**	SYNOPSIS: square root function
**
**	DESCRIPTION:
** 	return the nonnegative square root of x.
**
**	RETURN VALUE:
**   On success, these functions return the square root of x.
*/
double ft_sqrt(double x)
{
    double root;
    int i;

    if (x <= 0.0)
        return (0.0);
    root = x > 1.0 ? x : 1.0;
    i = 0;
    while (i++ < 64)
        root = 0.5 * (root + x / root);
    return (root);
}

// #include <stdio.h>
// int main() {
//     printf("sqrt(16)  = %f\n", ft_sqrt(16));   // Output: 4
//     printf("sqrt(-16)  = %f\n", ft_sqrt(-16));   // Output: 4
//     return 0;
// }