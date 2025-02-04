/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/20 13:40:06 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_strncmp(const char *s1, const char *s2, size_t n);

Description
   Compares up to `n` characters of the null-terminated strings `s1` and `s2`.
   The comparison is done lexicographically based on the ASCII values of the
	characters.
   If `n` is 0, the function returns 0 without performing any comparison.

Parameters
   #1. s1 : The first null-terminated string to compare.
   #2. s2 : The second null-terminated string to compare.
   #3. n  : The maximum number of characters to compare.

Return value
   An integer less than, equal to, or greater than 0, depending on whether
	`s1` is found to be
   less than, equal to, or greater than `s2` in the first `n` characters.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
