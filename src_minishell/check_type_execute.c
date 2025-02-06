/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:00:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/05 16:03:25 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_type_execute(t_btree *tree, char **envp)
{
	if (((t_node *)(tree->item))->type == COMMAND)
		pipes(tree, envp);
	else if (((t_node *)(tree->item))->type == PIPE)
		pipes(tree, envp);
	else if (((t_node *)(tree->item))->type == ECHO)
		echo(tree, envp);
	//a completer avec tous les builtin
}
