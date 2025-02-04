/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:45 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:27:14 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   void *ft_memchr(const void *s, int c, size_t n);

Description
   Scans the first `n` bytes of the memory area pointed to by `s` for the
	first occurrence of the byte `c`.
   The search is performed byte by byte.

Parameters
   #1. s : A pointer to the memory area to search in.
   #2. c : The byte to locate, passed as an `int` (converted to an
	unsigned char).
   #3. n : The number of bytes to search.

Return value
   A pointer to the first occurrence of the byte in the memory area, or `NULL`
	if the byte is not found within the first `n` bytes.
*/

void	*ft_memchr(const void *memoryBlock, int searchedChar, size_t size)
{
	size_t				count;
	unsigned char		c;
	const unsigned char	*str;

	if (size == 0)
		return (NULL);
	count = 0;
	str = (const unsigned char *)memoryBlock;
	c = (unsigned char)searchedChar;
	while (count < size)
	{
		if (*str == c)
			return ((void *)str);
		count++;
		str++;
	}
	return (NULL);
}
