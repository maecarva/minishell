/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:37 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 14:26:00 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   char *ft_strnstr(const char *haystack, const char *needle, size_t len);

Description
   Locates the first occurrence of the null-terminated string `needle` within
	the first `len` bytes of the string `haystack`.
   The function returns a pointer to the beginning of the found substring or
	`NULL` if the substring is not found within the specified length.

Parameters
   #1. haystack : The string to search within.
   #2. needle   : The substring to locate.
   #3. len      : The maximum number of bytes to search in `haystack`.

Return value
   A pointer to the beginning of the located substring if found; otherwise,
	`NULL` if the substring is not found within `len` bytes.
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t size)
{
	size_t	count;
	size_t	tmp_count;

	if (needle[0] == '\0')
		return ((char *)haystack);
	if (size == 0)
		return (NULL);
	count = 0;
	while (haystack[count] && count < size)
	{
		tmp_count = 0;
		while (haystack[count + tmp_count] && (count + tmp_count) < size
			&& haystack[count + tmp_count] == needle[tmp_count])
		{
			tmp_count++;
			if (needle[tmp_count] == '\0')
				return ((char *)haystack + count);
		}
		count++;
	}
	return (NULL);
}
