/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_level_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 13:33:12 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 10:02:58 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

int	ft_btree_level_count(t_btree *root)
{
	int	level_left;
	int	level_right;
	int	count;

	if (root == NULL)
		return (0);
	level_left = ft_btree_level_count(root->left);
	level_right = ft_btree_level_count(root->right);
	if (level_left >= level_right)
		count = level_left;
	else
		count = level_right;
	return (1 + count);
}
