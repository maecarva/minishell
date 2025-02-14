/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_char_in_charset_rev.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:58:17 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/14 16:07:34 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	ft_first_char_in_charset_rev(char *s, char *charset, int index)
{
	if (!s || !charset)
		return ('\0');
	while (index >= 0)
	{
		if (ft_is_in_charset(s[index], charset))
			return (s[index]);
		index--;
	}
	return ('\0');
}
