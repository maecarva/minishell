/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:50 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:51:21 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_tolower(int c);

Description
   Converts an uppercase alphabetic character to its corresponding lowercase
	equivalent.
   If the input character is not an uppercase letter, it is returned unchanged.

Parameters
   #1. c : The character to be converted, passed as an `int`
	(typically a `char`).

Return value
   The lowercase equivalent of the character if it is uppercase; otherwise,
	the character itself is returned unchanged.
*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
