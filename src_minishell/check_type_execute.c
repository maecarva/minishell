/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_execute.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:00:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 18:34:07 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_type_execute(t_config *ms_data)
{
	if (ms_data->tree->item->type == COMMAND)
		pipes(ms_data);
	else if (ms_data->tree->item->type == PIPE)
		pipes(ms_data);
	// else if (((t_node *)(tree->item))->type == ECHO)
	// 	echo(tree, envp);
	//a completer avec tous les builtin
}
