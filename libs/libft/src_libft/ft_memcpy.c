/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:51 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 13:09:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   void *ft_memcpy(void *dest, const void *src, size_t n);

Description
   Copies `n` bytes from the memory area `src` to the memory area `dest`.  
   The memory areas must not overlap.

Parameters
   #1. dest : A pointer to the destination memory area where the content
	is copied.
   #2. src : A pointer to the source memory area from where the content
	is copied.
   #3. n : The number of bytes to copy.

Return value
   The function returns a pointer to the destination memory area `dest`.
*/

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	unsigned char		*tmp_dest;
	const unsigned char	*tmp_src;

	if (!dest && !src)
		return (NULL);
	tmp_dest = (unsigned char *)dest;
	tmp_src = (const unsigned char *)src;
	if (tmp_dest == tmp_src || count == 0)
		return (dest);
	while (count > 0)
	{
		*(tmp_dest++) = *(tmp_src++);
		count--;
	}
	return (dest);
}
