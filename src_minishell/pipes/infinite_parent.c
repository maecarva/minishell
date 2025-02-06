/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 18:47:52 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	mid_child(t_pipes *p_data, int i)
{
	close(p_data->fd[i][0]);
	if (dup2(p_data->fd[i - 1][0], STDIN_FILENO) == -1)
	{
		close(p_data->fd[i - 1][0]);
		close(p_data->fd[i][1]);
		free_minishell(&(p_data->ms_data));
		free_fd(&(p_data->fd), p_data->nb_pipes);
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[i - 1][0]);
	if (dup2(p_data->fd[i][1], STDOUT_FILENO) == -1)
	{
		close(p_data->fd[i][1]);
		free_minishell(&(p_data->ms_data));
		free_fd(&(p_data->fd), p_data->nb_pipes);
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[i][1]);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	execute_command(p_data);
}

// static void	free_check_mid(t_pipes *p_data)
// {
// 	free_fds(p_data->fd, p_data->nb_pipes);
// 	check_children(p_data);
// }

void	infinite_parent(t_pipes *p_data)
{
	int		i;
	pid_t	pid;

	i = 1;
	while (i < p_data->nb_pipes)
	{
		p_data->ms_data->tree = p_data->ms_data->tree->right;
		close((p_data->fd)[i - 1][1]);
		if (pipe(p_data->fd[i]) == -1)
		{
			free_minishell(&(p_data->ms_data));
			free_fd(&(p_data->fd), p_data->nb_pipes);
			ft_perror("pipe", ERROR_CODE);
		}
		pid = fork();
		if (pid < 0)
		{
			close((p_data->fd)[i - 1][0]);
			free_minishell(&(p_data->ms_data));
			free_fd(&(p_data->fd), p_data->nb_pipes);
			ft_perror("pid", ERROR_CODE);
		}
		if (pid == 0)
			mid_child(p_data, i);
		close((p_data->fd)[i - 1][0]);
		i++;
	}
	close((p_data->fd)[i - 1][1]);
}
