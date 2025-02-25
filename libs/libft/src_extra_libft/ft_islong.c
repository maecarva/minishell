/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_islong.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:53:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/24 14:55:40 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_islong(char *str)
{
	__int128_t	nb;
	int			count;
	int			sign;

	nb = 0;
	count = 0;
	sign = 1;
	while ((str[count] >= 9 && str[count] <= 13) || str[count] == ' ')
		count++;
	if (str[count] == '+')
		count++;
	else if (str[count] == '-')
	{
		sign = -1;
		count++;
	}
	while (ft_isdigit(str[count]))
	{
		nb = nb * 10 + (str[count] - '0') * sign;
		if (nb > (__int128_t)LONG_MAX || nb < (__int128_t)LONG_MIN)
			return (false);
		count++;
	}
	return (true);
}
