/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:13:55 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:22:25 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   void ft_bzero(void *s, size_t n);

Description
   Sets the first `n` bytes of the memory area pointed to by `s` to zero.

Parameters
   #1. s : A pointer to the memory area to be set to zero.
   #2. n : The number of bytes to set to zero.

Return value
   This function does not return a value.
*/

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*tmp_ptr;

	tmp_ptr = (unsigned char *)s;
	while (n > 0)
	{
		*(tmp_ptr++) = 0;
		n--;
	}
}
