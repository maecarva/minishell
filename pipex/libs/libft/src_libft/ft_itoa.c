/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:16 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:41:58 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	char *ft_itoa(int n);

Description
	Allocates (with malloc(3)) and returns a string 
	representing the integer received as an argument.
	Negative numbers must be handled.

Parameters
	#1. the integer to convert.

Return value
	The string representing the integer. NULL if the allocation fails.
*/

static size_t	count_malloc(int n)
{
	size_t	count;

	count = 0;
	if (n <= 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*s;
	size_t	s_len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s_len = count_malloc(n);
	s = malloc(sizeof(char) * (s_len + 1));
	if (!s)
		return (NULL);
	s[s_len] = '\0';
	if (n == 0)
		s[0] = '0';
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	while (n != 0)
	{
		s[s_len - 1] = (n % 10) + '0';
		n /= 10;
		s_len--;
	}
	return (s);
}
