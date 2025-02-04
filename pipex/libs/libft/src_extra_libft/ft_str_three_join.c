/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_three_join.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:48:04 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/21 18:07:03 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_three_join(char const *s1, char const *s2, char const *s3)
{
	char	*s;
	int		i;
	int		j;
	int		k;

	if (!s1 || !s2 || !s3)
		return (NULL);
	s = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1));
	if (!s)
		return (NULL);
	i = -1;
	while (s1[++i])
		s[i] = s1[i];
	j = -1;
	while (s2[++j])
		s[i + j] = s2[j];
	k = -1;
	while (s3[++k])
		s[i + j + k] = s3[k];
	s[i + j + k] = '\0';
	return (s);
}
