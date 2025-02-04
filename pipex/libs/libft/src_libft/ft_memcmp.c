/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:48 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 13:46:30 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_memcmp(const void *s1, const void *s2, size_t n);

Description
   Compares the first `n` bytes of the memory areas `s1` and `s2`.
   The comparison is performed byte by byte, interpreting the bytes as
	unsigned char values.

Parameters
   #1. s1 : A pointer to the first memory area.
   #2. s2 : A pointer to the second memory area.
   #3. n  : The number of bytes to compare.

Return value
   An integer less than, equal to, or greater than 0, depending on whether
	the first `n` bytes of `s1` are found to be
   less than, equal to, or greater than the first `n` bytes of `s2`.
*/

int	ft_memcmp(const void *pointer1, const void *pointer2, size_t size)
{
	const char	*ptr1;
	const char	*ptr2;
	size_t		count;

	if (size == 0)
		return (0);
	count = 0;
	ptr1 = (const char *)pointer1;
	ptr2 = (const char *)pointer2;
	while (count < size - 1 && ptr1[count] == ptr2[count])
		count++;
	return ((unsigned char)ptr1[count] - (unsigned char)ptr2[count]);
}
