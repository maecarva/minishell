/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:28:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/07 14:13:33 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	simple_child(t_pipes *p_data)
{
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
	{
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	execute_command(p_data);
}

void	simple_command(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		free_minishell(&(p_data->ms_data));
		ft_perror("fork", ERROR_CODE);
	}
	if (pid == 0)
		simple_child(p_data);
	p_data->pid_last_parent = pid;
}
