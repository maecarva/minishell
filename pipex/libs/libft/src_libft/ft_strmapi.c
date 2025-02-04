/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:30 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:37:27 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	char *ft_strmapi(char const *s, char (*f)(unsigned int, char));

Description
	Applies the function ’f’ to each character of the
	string ’s’ to create a new string (with malloc(3))
	resulting from successive applications of ’f’.

Parameters
	#1. The string on which to iterate.
	#2. The function to apply to each character.

Return value
	The string created from the successive applications
	of ’f’. Returns NULL if the allocation fails.
*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (s[i])
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}
