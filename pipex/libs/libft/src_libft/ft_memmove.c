/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:55 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:28:19 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   void *ft_memmove(void *dest, const void *src, size_t n);

Description
   Copies `n` bytes from the memory area `src` to the memory area `dest`.
	Unlike `memcpy`, `memmove` handles overlapping memory areas correctly.

Parameters
   #1. dest : A pointer to the destination memory area where the content
	is copied.
   #2. src : A pointer to the source memory area from where the content
	is copied.
   #3. n : The number of bytes to copy.

Return value
   The function returns a pointer to the destination memory area `dest`.
*/

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char		*ptr_dest;
	const unsigned char	*ptr_src;

	if (!dest || !src)
		return (NULL);
	ptr_dest = (unsigned char *)dest;
	ptr_src = (const unsigned char *)src;
	if (ptr_dest == ptr_src || count == 0)
		return (dest);
	if (ptr_dest > ptr_src && ptr_dest < ptr_src + count)
	{
		while (count--)
			*(ptr_dest + count) = *(ptr_src + count);
	}
	else
	{
		while (count--)
			*(ptr_dest++) = *(ptr_src++);
	}
	return (dest);
}
