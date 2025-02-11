/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:00:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 13:37:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_type_execute(t_config *ms_data)
{
	if (((t_node2 *)(ms_data->ast->item))->type == CMD)
		pipes(ms_data);
	else if (((t_node2 *)(ms_data->ast->item))->type == PIPE_TOKEN)
		pipes(ms_data);
	// else if (((t_node *)(tree->item))->type == ECHO)
	// 	echo(tree, envp);
	//a completer avec tous les builtin
}
