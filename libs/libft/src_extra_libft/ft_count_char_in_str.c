/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char_in_str.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 15:52:30 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/14 15:52:31 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_char_in_str(char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (count);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}
