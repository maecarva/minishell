/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dll_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 18:30:17 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 12:21:27 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_libft/libft.h"

void	dll_insert(t_dlist *l1, t_dlist *l2)
{
	t_dlist	*tail1;
	t_dlist	*tail2;

	if (!l1 || !l2)
		return ;
	tail1 = l1->prev;
	tail2 = l2->prev;
	tail1->next = l2;
	l2->prev = tail1;
	tail2->next = l1;
	l1->prev = tail2;
}
