/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 15:07:02 by maecarva          #+#    #+#             */
/*   Updated: 2024/12/24 15:34:48 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_libft/libft.h"

static void	finish(t_dlist *tmp, t_dlist **dlist, t_dlist *new_elem)
{
	while (tmp->next != *dlist)
		tmp = tmp->next;
	tmp->next = new_elem;
	new_elem->prev = tmp;
	new_elem->next = *dlist;
	(*dlist)->prev = new_elem;
}

t_dlist	*dll_add_back(t_dlist **dlist, t_dlist *new_elem)
{
	t_dlist	*tmp;
	int		size;

	if (!new_elem)
		return (*dlist);
	if (!(*dlist))
	{
		*dlist = new_elem;
		(*dlist)->next = *dlist;
		(*dlist)->prev = *dlist;
		return (*dlist);
	}
	size = dll_size(dlist);
	tmp = *dlist;
	if (size == 1)
	{
		(*dlist)->next = new_elem;
		(*dlist)->prev = new_elem;
		new_elem->next = (*dlist);
		new_elem->prev = (*dlist);
		return (*dlist);
	}
	finish(tmp, dlist, new_elem);
	return (*dlist);
}
