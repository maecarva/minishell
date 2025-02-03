/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:25 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 09:50:09 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   size_t ft_strlcpy(char *dest, const char *src, size_t size);

Description
   Copies up to `size - 1` characters from the string `src` to the
	string `dest`,and ensures the destination string is null-terminated.  
   If `src` is longer than `size - 1`, it will be truncated.

Parameters
   #1. dest : A pointer to the destination buffer where the content is copied.
   #2. src : A pointer to the source string to be copied.
   #3. size : The size of the destination buffer, including the space for the
	null terminator.

Return value
   The function returns the total length of the string it tried to create,
	i.e.,the length of `src`.
   If the return value is greater than or equal to `size`, the string was
	truncated.
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	len_src;
	size_t	count;

	len_src = ft_strlen(src);
	if (size == 0)
		return (len_src);
	count = 0;
	while (src[count] && count < size - 1)
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (len_src);
}
