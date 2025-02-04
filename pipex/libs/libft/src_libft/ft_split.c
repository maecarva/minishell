/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:10 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/05 02:00:49 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	char **ft_split(char const *s, char c);

Description
	Allocates (with malloc(3)) and returns an array of strings 
	obtained by splitting ’s’ using the character ’c’ as a delimiter.
	The array must be ended by a NULL pointer.

Parameters
	#1. The string to be split.
	#2. The delimiter character.

Return value
	The array of new strings resulting from the split.
	NULL if the allocation fails.
*/

static size_t	count_malloc_split_big(char const *s, char c)
{
	size_t	count;
	size_t	size;
	int		inorout;

	inorout = 0;
	count = 0;
	size = 0;
	while (s[count] != '\0')
	{
		if (s[count] == c)
		{
			if (inorout == 1)
			{
				size++;
				inorout = 0;
			}
		}
		else
			inorout = 1;
		count++;
	}
	if (inorout == 1)
		size++;
	return (size);
}

static char	**free_split(char **dest)
{
	int	count;

	count = 0;
	while (dest[count] != NULL)
	{
		free(dest[count]);
		count++;
	}
	free(dest);
	return (NULL);
}

static char	*create_cpy(char const *s, char c)
{
	size_t	j;

	j = 0;
	while (*(s + j) && *(s + j) != c)
		j++;
	return (ft_substr(s, 0, j));
}

char	**ft_split(char const *s, char c)
{
	char	**dst;
	size_t	count;

	if (!s)
		return (NULL);
	dst = malloc(sizeof(char *) * (count_malloc_split_big(s, c) + 1));
	if (!dst)
		return (NULL);
	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			dst[count] = create_cpy(s, c);
			if (!dst[count])
				return (free_split(dst));
			s += ft_strlen(dst[count]);
			count++;
		}
		else
			s++;
	}
	dst[count] = NULL;
	return (dst);
}
