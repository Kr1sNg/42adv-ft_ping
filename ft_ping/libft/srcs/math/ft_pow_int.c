/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tat-nguy <tat-nguy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/23 11:47:32 by tat-nguy          #+#    #+#             */
/*   Updated: 2026/10/23 11:55:28 by tat-nguy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	LIBRARY: math.h
**	SYNOPSIS: power function
**
**	DESCRIPTION:
** 	power function supporting double base raised to the power of integer power.
**
**	RETURN VALUE:
**  On success, these functions return the value of base to the power of power.
*/
double ft_pow_int(double base, int power)
{
    if (power == 0)
        return (1.0);

    long long exp = power;
    if (exp < 0)
    {
        base = 1.0 / base;
        exp = -exp;
    }

    double result = 1.0;
    while (exp > 0)
    {
        if (exp % 2 == 1)
            result *= base;
        base *= base;
        exp /= 2;
    }
    return (result);
}

// #include <stdio.h>
// int main() {
//     printf("2.5^3  = %f\n", ft_pow_int(2.5, 3));   // Output: 15.625000
//     printf("2.0^-3 = %f\n", ft_pow_int(2.0, -3));  // Output: 0.125000
//     return 0;
// }