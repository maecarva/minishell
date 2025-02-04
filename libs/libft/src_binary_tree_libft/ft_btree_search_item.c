/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:34:11 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/30 17:34:04 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*ft_btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void *, void *))
{
	int		cmp;
	void	*found_left;

	if (root == NULL)
		return (NULL);
	found_left = ft_btree_search_item(root->left, data_ref, cmpf);
	if (found_left != NULL)
		return (found_left);
	cmp = cmpf(root->item, data_ref);
	if (cmp == 0)
		return (root->item);
	return (ft_btree_search_item(root->right, data_ref, cmpf));
}
