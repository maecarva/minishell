/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:05 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:24:56 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_isascii(int c);

Description
   Checks whether the given character is a valid ASCII character (in the
	range 0 to 127).

Parameters
   #1. c : The character to check, passed as an `int` (typically a `char`).

Return value
   The function returns a non-zero value if the character is a valid ASCII
	character (0-127), and 0 if it is not.
*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
