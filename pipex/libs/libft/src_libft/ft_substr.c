/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:47 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:49:37 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	char *ft_substr(char const *s, unsigned int start, size_t len);

Parameters
	#1. The string from which to create the substring.
	#2. The start index of the substring in the string ’s’.
	#3. The maximum length of the substring.

Description
	Allocates (with malloc(3)) and returns a substring from the string ’s’.
	The substring begins at index ’start’ and is of maximum size ’len’.

Return value
	The substring. NULL if the allocation fails
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*dest;
	char	*src;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start)
		return (ft_strdup(""));
	if (s_len - start < len)
		len = s_len - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	src = (char *)s + start;
	ft_strlcpy(dest, src, len + 1);
	return (dest);
}
