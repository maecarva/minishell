/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:43:54 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/13 21:12:16 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

t_btree	*create_operator_node(t_lexertok type)
{
	t_node2	*node;

	node = ft_calloc(sizeof(t_node2), 1);
	if (!node)
		return (NULL);
	node->type = type;
	node->command = NULL;
	node->file = NULL;
	return (ft_btree_create_node(node));
}
