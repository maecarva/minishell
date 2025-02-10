/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/07 14:13:00 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	last_child(t_pipes *p_data)
{
	if (dup2(p_data->fd[p_data->nb_pipes - 1][0], STDIN_FILENO) == -1)
	{
		close(p_data->fd[p_data->nb_pipes - 1][0]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[p_data->nb_pipes - 1][0]);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
	{
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmd = p_data->ms_data->tree->right->item->cmd->cmd;
	execute_command(p_data);
}

void	last_parent(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(p_data->fd[p_data->nb_pipes - 1][0]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("pid", ERROR_CODE);
	}
	if (pid == 0)
		last_child(p_data);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->pid_last_parent = pid;
}
