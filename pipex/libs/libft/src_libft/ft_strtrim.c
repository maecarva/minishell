/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:44 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:41:54 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	char *ft_strtrim(char const *s1, char const *set);
Description
	Allocates (with malloc(3)) and returns a copy of
	’s1’ with the characters specified in ’set’ removed
	from the beginning and the end of the string.
Parameters
	#1. The string to be trimmed.
	#2. The reference set of characters to trim.
Return value
	The trimmed string. NULL if the allocation fails.
*/

static int	is_in_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*dst;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (start < end && is_in_set(s1[start], set))
		start++;
	while (start < end && is_in_set(s1[end - 1], set))
		end--;
	dst = malloc(sizeof(char) * (end - start + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1 + start, end - start + 1);
	return (dst);
}
