/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/14 18:16:03 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	mid_child(t_pipes *p_data, int i)
{
	close(p_data->fd[i][0]);
	if (dup2(p_data->fd[i - 1][0], STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(p_data->fd[i - 1][0]);
		close(p_data->fd[i][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	close(p_data->fd[i - 1][0]);
	if (dup2(p_data->fd[i][1], STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(p_data->fd[i][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	close(p_data->fd[i][1]);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->left->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->left->item))->type;
	execute_command(p_data);
}

void	infinite_parent(t_pipes *p_data)
{
	int		i;
	pid_t	pid;

	i = 1;
	while (i < p_data->nb_pipes)
	{
		p_data->ms_data->ast = p_data->ms_data->ast->right;
		close((p_data->fd)[i - 1][1]);
		if (pipe(p_data->fd[i]) == -1)
		{
			perror("pipe");
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("pid");
			close((p_data->fd)[i - 1][0]);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
		}
		if (pid == 0)
			mid_child(p_data, i);
		close((p_data->fd)[i - 1][0]);
		i++;
	}
	close((p_data->fd)[i - 1][1]);
}
