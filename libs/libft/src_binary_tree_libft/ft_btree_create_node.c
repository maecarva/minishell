/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 15:33:42 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/30 17:33:53 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*ft_btree_create_node(void *item)
{
	t_btree	*new_elem;

	new_elem = malloc(sizeof(t_btree));
	if (!new_elem)
		return (NULL);
	new_elem->item = item;
	new_elem->left = NULL;
	new_elem->right = NULL;
	return (new_elem);
}
