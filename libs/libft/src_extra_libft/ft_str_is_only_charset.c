/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strisonly.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:38:37 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/15 14:41:46 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_str_is_only_charset(char *str, char *charset)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_is_in_charset(str[i], charset) == false)
			return (false);
		i++;
	}
	return (true);
}
