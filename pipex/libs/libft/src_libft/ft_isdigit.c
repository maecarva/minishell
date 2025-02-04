/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:08 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:30:38 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   int ft_isdigit(int c);

Description
   Checks whether the given character is a decimal digit (0 through 9).

Parameters
   #1. c : The character to check, passed as an `int` (typically a `char`).

Return value
   The function returns a non-zero value if the character is a digit (0-9),
	and 0 if it is not.
*/

int	ft_isdigit(int c)
{
	if ((c >= '0' && c <= '9'))
		return (1);
	return (0);
}
