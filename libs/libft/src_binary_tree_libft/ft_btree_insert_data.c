/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_insert_data.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:45:23 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 10:02:03 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_btree_insert_data(t_btree **root, void *item,
		int (*cmpf)(void *, void *))
{
	int		comp;

	if ((*root) == NULL)
	{
		(*root) = ft_btree_create_node(item);
		return ;
	}
	comp = cmpf(item, (*root)->item);
	if (comp < 0)
		ft_btree_insert_data(&((*root)->left), item, cmpf);
	else
		ft_btree_insert_data(&((*root)->right), item, cmpf);
}
