/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:22:12 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 18:43:42 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	free(cmd->cmd);
	free(cmd);
}

void	free_node(t_node *node)
{
	if (!node)
		return ;
	if (node->type == COMMAND)
	{
		free(node->cmd->input_file);
		free(node->cmd->output_file);
		free(node->cmd->identifier);
		free_cmd(node->cmd);
	}
	free(node);
}

void	clear_ast(t_btree *ast)
{
	if (!ast)
		return ;
	clear_ast(ast->left);
	clear_ast(ast->right);
	free_node((t_node *)(ast->item));
	free(ast);
}
