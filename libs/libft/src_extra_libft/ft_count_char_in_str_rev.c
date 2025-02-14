/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char_in_str_rev.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:52:24 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/14 15:53:25 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char_in_str_rev(char *str, char c, int index)
{
	int	count;

	count = 0;
	if (!str)
		return (count);
	while (index >= 0)
	{
		if (str[index] == c)
			count++;
		index--;
	}
	return (count);
}
