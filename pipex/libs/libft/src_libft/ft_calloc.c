/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:13:58 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 14:07:15 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   void *ft_calloc(size_t count, size_t size);

Description
   Allocates memory for an array of `count` elements, each of size `size`,
	and initializes all the bytes to zero.
   It is equivalent to calling `malloc(count * size)` followed by `memset`
	to zero the allocated memory.

Parameters
   #1. count : The number of elements to allocate.
   #2. size  : The size of each element.

Return value
   A pointer to the allocated memory block. If the allocation fails,
	`NULL` is returned.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*tmp_ptr;

	if (count != 0 && size > SIZE_MAX / count)
		return (NULL);
	tmp_ptr = malloc(count * size);
	if (!tmp_ptr)
		return (NULL);
	ft_bzero(tmp_ptr, count * size);
	return (tmp_ptr);
}
