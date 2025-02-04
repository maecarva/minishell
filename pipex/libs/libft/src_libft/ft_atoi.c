/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:13:50 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:19:54 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_atoi(const char *str);

Description
   Converts the initial portion of the string pointed to by `str`
	to an integer (of type `int`).
   The conversion stops when a non-digit character is encountered
	or the string ends.
   Leading whitespace characters are ignored, and a negative sign
	(`-`) indicates a negative integer.

Parameters
   #1. str : The string to convert to an integer. The string may include 
	leading whitespace and an optional sign.

Return value
   The integer representation of the string, or 0 if no valid conversion
	could be performed.
*/

int	ft_atoi(const char *str)
{
	int	nb;
	int	count;
	int	sign;

	nb = 0;
	count = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == ' ')
		count++;
	if (str[count] == '+')
		count++;
	else if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	while (ft_isdigit(str[count]))
	{
		nb = nb * 10 + (str[count] - '0') * sign;
		count++;
	}
	return (nb);
}
