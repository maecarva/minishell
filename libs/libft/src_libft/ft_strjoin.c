/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:15:20 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 17:43:25 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Prototype
	char *ft_strjoin(char const *s1, char const *s2);

Description
	Allocates (with malloc(3)) and returns a new string, 
	which is the result of the concatenation of ’s1’ and ’s2’.

Paramètres
	#1. The prefix string.
	#2. The suffix string.

Valeur de retour
	The new string. NULL if the allocation fails.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		s[i + j] = s2[j];
		j++;
	}
	s[i + j] = '\0';
	return (s);
}
