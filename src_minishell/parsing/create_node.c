/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:55 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 14:54:04 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

t_btree	*create_special_node(t_token nodetype)
{
	t_btree	*new_node;
	t_node	*node_content;

	node_content = ft_calloc(sizeof(t_node), 1);
	if (!node_content)
		return NULL;
	node_content->type = nodetype;
	node_content->cmd = NULL;
	new_node = ft_btree_create_node(node_content);
	if (!new_node)
		return (free(node_content), NULL);
	return (new_node);
}

t_btree	*create_command_node(char **cmd_split)
{
	int		i;
	t_cmd	*cmd;
	t_node	*node_content;
	t_btree	*new_node;

	if (!cmd_split)
		return (NULL);
	i = 0;
	while (cmd_split[i] == NULL)
		i++;
	node_content = ft_calloc(sizeof(t_node), 1);
	if (!node_content)
		return NULL;
	node_content->type = COMMAND;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_strdup(cmd_split[i]);
	if (!cmd->cmd)
		return (free(cmd), NULL);
	cmd->quotes = false;
	
	node_content->cmd = cmd;

	new_node = ft_calloc(sizeof(t_btree), 1);
	if (!new_node)
		return (free(cmd->cmd), free(cmd), NULL);
	new_node->item = node_content;
	return (new_node);
}
