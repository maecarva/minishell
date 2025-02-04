/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:46:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 18:39:43 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

int	count_pipes(t_btree	*arbre)
{
	int	count;

	if (!arbre)
		return (0);
	count = 0;
	//print_arbre(arbre, 0);
	while (arbre && ((t_node *)arbre->item)->type == PIPE)
	{
		count++;
		arbre = arbre->right;
	}
	return (count);
}
