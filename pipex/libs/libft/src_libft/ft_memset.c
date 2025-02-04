/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:57 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:28:29 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   void *ft_memset(void *s, int c, size_t n);

Description
   Fills the first `n` bytes of the memory area pointed to by `s` with
	the constant byte `c`.

Parameters
   #1. s : A pointer to the memory area to fill.
   #2. c : The value to set. It is passed as an `int`, but the function fills
	the memory with its unsigned char equivalent.
   #3. n : The number of bytes to set to the value `c`.

Return value
   The function returns a pointer to the memory area `s`.
*/

void	*ft_memset(void *dest, int c, size_t count)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)dest;
	while (count > 0)
	{
		*(tmp_ptr++) = (unsigned char)c;
		count--;
	}
	return (dest);
}
