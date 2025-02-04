/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:52 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:51:51 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int toupper(int c);

Description
   Converts a lowercase alphabetic character to its corresponding uppercase
	equivalent.
   If the input character is not a lowercase letter, it is returned unchanged.

Parameters
   #1. c : The character to be converted, passed as an `int`
	(typically a `char`).

Return value
   The uppercase equivalent of the character if it is lowercase; otherwise,
	the character itself is returned unchanged.
*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
