/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:41:56 by maecarva          #+#    #+#             */
/*   Updated: 2024/12/24 15:49:26 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_libft/libft.h"

void	dll_clear(t_dlist **dlist)
{
	t_dlist	*tmp;
	int		size;

	size = dll_size(dlist);
	tmp = *dlist;
	while (size > 0)
	{
		tmp = tmp->next;
		free(*dlist);
		*dlist = tmp;
		size--;
	}
	*dlist = NULL;
}
