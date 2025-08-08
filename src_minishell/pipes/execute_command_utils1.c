/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command_utils1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:46:00 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 13:27:39 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_pipes *d)
{
	if (d->type == ECHO)
		execute_echo(((t_node2 *)(d->ms_data->ast->item))->command, d->ms_data);
	else if (((t_node2 *)(d->ms_data->ast->item))->type == PWD)
		execute_pwd(((t_node2 *)(d->ms_data->ast->item))->command, d->ms_data);
	else if (((t_node2 *)(d->ms_data->ast->item))->type == ENV)
		execute_env(((t_node2 *)(d->ms_data->ast->item))->command, d->ms_data);
	else if (((t_node2 *)(d->ms_data->ast->item))->type == EXIT)
		execute_exit(((t_node2 *)(d->ms_data->ast->item))->command, d->ms_data);
	else if (((t_node2 *)(d->ms_data->ast->item))->type == CD)
		execute_cd(((t_node2 *)(d->ms_data->ast->item))->command, d->ms_data);
	else if (((t_node2 *)(d->ms_data->ast->item))->type == UNSET)
		execute_unset(((t_node2 *)(d->ms_data->ast->item))->command,
			d->ms_data);
	else if (((t_node2 *)(d->ms_data->ast->item))->type == EXPORT)
		execute_export(((t_node2 *)(d->ms_data->ast->item))->command,
			d->ms_data);
	else
		return (0);
	return (1);
}
