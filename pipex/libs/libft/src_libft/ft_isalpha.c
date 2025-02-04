/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:14:03 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 09:24:44 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Prototype
   int ft_isalpha(int c);

Description
   Checks whether the given character is an alphabetic letter (either lowercase
	or uppercase).

Parameters
   #1. c : The character to check, passed as an `int` (typically a `char`).

Return value
   The function returns a non-zero value if the character is alphabetic,
	and 0 if it is not.
*/

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}
