/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 17:36:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 17:42:38 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_skip_spaces(char *str, int *i)
{
	if (*i >= (int)ft_strlen(str))
		return ;
	while (str[*i])
		(*i)++;
}
