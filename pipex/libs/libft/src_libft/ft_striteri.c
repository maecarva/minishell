/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:17 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 09:46:27 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	void ft_striteri(char *s, void (*f)(unsigned int, char*));

Description
	Applies the function f to each character of the
	string passed as argument, and passing its index
	as first argument. Each character is passed by
	address to f to be modified if necessary

Parameters
	#1. The string on which to iterate.
	#2. The function to apply to each character.

Return value
	None.
*/

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
