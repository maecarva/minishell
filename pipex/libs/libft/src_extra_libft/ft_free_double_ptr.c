/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_ptr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:10:43 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/20 14:58:34 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_double_ptr(char ***split)
{
	int	i;

	if (split && *split)
	{
		i = 0;
		while ((*split)[i])
		{
			free((*split)[i]);
			i++;
		}
		free(*split);
		*split = NULL;
	}
}
