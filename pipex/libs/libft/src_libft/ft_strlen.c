/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:28 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:37:18 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   size_t ft_strlen(const char *str);

Description
   Computes the length of the given string, excluding the null-terminator.

Parameters
   #1. str : A pointer to the string to check, which must be null-terminated.

Return value
   The function returns the number of characters in the string, excluding the
	terminating null byte (`\0`).
*/

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}
