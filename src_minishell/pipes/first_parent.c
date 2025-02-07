/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: x03phy <x03phy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/07 14:10:52 by x03phy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	first_child(t_pipes *p_data)
{
	close (p_data->fd[0][0]);
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		close(p_data->fd[0][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	if (dup2(p_data->fd[0][1], STDOUT_FILENO) == -1)
	{
		close(p_data->fd[0][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[0][1]);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmd = p_data->ms_data->tree->left->item->cmd->cmd;
	execute_command(p_data);
}

void	first_parent(t_pipes *p_data)
{
	pid_t	pid;

	if (pipe(p_data->fd[0]) == -1)
	{
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("pipe", ERROR_CODE);
	}
	pid = fork();
	if (pid < 0)
	{
		close(p_data->fd[0][0]);
		close(p_data->fd[0][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("fork", ERROR_CODE);
	}
	if (pid == 0)
		first_child(p_data);
}
