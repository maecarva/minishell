/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:11:09 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 15:32:48 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

static void	destroy_hd(t_btree *node)
{
	if (((t_node2 *)(node->item))->type == HEREDOC)
	{
		if (unlink(((t_node2 *)(node->item))->file) == -1)
			perror("unlink");
	}
}

void	clear_here_doc(t_btree *root)
{
	if (root == NULL)
		return ;
	if (root->left)
		clear_here_doc(root->left);
	destroy_hd(root);
	if (root->right)
		clear_here_doc(root->right);
}

int	clear_minishell(t_config *minishell)
{
	int	errorcode;

	if (!minishell)
		return (0);
	rl_clear_history();
	minishell->ast = minishell->dont_fucking_touch_me;
	clear_here_doc(minishell->ast);
	free_ast(&(minishell->dont_fucking_touch_me));
	errorcode = minishell->last_error_code;
	if (minishell->prompt)
		free(minishell->prompt);
	if (minishell->current_path)
		free(minishell->current_path);
	if (minishell->environnement)
		ft_free_double_ptr(&minishell->environnement);
	if (minishell->pidstr && ft_strcmp(minishell->pidstr, "-1") != 0)
		free(minishell->pidstr);
	free(minishell);
	exit(errorcode);
}
