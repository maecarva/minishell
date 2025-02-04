/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:41 by ebonutto          #+#    #+#             */
/*   Updated: 2024/11/12 11:41:50 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
   char *ft_strrchr(const char *s, int c);

Description
   Locates the last occurrence of the character `c` (converted to a `char`)
	in the string `s`.
   The terminating null byte is considered part of the string, so the function
	can also locate `'\0'`.

Parameters
   #1. s : The null-terminated string to search in.
   #2. c : The character to locate, passed as an `int`.

Return value
   A pointer to the last occurrence of the character in the string, or `NULL`
	if the character is not found.
*/

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			last = (char *)s;
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (last);
}
