/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_size_between.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:07:40 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/09 15:10:53 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_libft/libft.h"

int	dll_size_between(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;
	int		size;

	if (!start || !end)
		return (0);
	if (start == end)
		return (1);
	tmp = start;
	size = 1;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
		if (tmp == end || tmp == start)
			break ;
	}
	return (size);
}
