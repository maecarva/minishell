/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:15 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:34:20 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   char *ft_strdup(const char *s1);

Description
   Allocates memory and returns a copy of the string `s1`.

Parameters
   #1. s1 : The string to duplicate. It must be a null-terminated string.

Return value
   The function returns a pointer to the newly duplicated string. 
   If memory allocation fails, it returns `NULL`.
*/

char	*ft_strdup(const char *src)
{
	char		*dest;
	size_t		src_len;
	size_t		count;

	if (!src)
		return (NULL);
	src_len = ft_strlen(src);
	dest = malloc(sizeof(char) * (src_len + 1));
	if (!dest)
		return (NULL);
	count = 0;
	while (src[count])
	{
		dest[count] = src[count];
		count++;
	}
	dest[count] = '\0';
	return (dest);
}
