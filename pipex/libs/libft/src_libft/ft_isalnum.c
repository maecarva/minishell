/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:01 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:24:05 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_isalnum(int c);

Description
   Checks whether the given character is alphanumeric (either a letter
	or a digit).

Parameters
   #1. c : The character to check, passed as an `int` (typically a `char`).

Return value
   The function returns a non-zero value if the character is alphanumeric
	(a letter or a digit), and 0 if it is not.
*/

int	ft_isalnum(int c)
{
	if ((ft_isalpha(c) || ft_isdigit(c)))
		return (1);
	return (0);
}
