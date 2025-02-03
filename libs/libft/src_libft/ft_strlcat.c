/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:23 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:35:46 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   size_t ft_strlcat(char *dst, const char *src, size_t dstsize);

Description
   Appends the null-terminated string `src` to the end of `dst`, ensuring the
	result fits within `dstsize` bytes, including the null terminator. 
	The function guarantees null-termination if `dstsize` is greater than 0.

Parameters
   #1. dst : The destination string buffer, which must have enough space for
	the result.
   #2. src : The source string to append to `dst`.
   #3. dstsize : The size of the buffer pointed to by `dst`.

Return value
   The total length of the string it tried to create, which is the initial
	length of `dst` plus the length of `src`.
   If the return value is greater than or equal to `dstsize`,
	truncation occurred.
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	size_dest;
	size_t	count;
	size_t	size_src;

	size_dest = ft_strlen(dest);
	size_src = ft_strlen(src);
	if (size <= size_dest)
		return (size + size_src);
	count = 0;
	while (src[count] && count < size - size_dest - 1)
	{
		dest[size_dest + count] = src[count];
		count++;
	}
	dest[size_dest + count] = '\0';
	return (size_dest + size_src);
}
