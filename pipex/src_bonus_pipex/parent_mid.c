/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_mid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:45:07 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 13:11:46 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	mid_child(t_pipex d, int i)
{
	close(d.fd[i][0]);
	if (dup2(d.fd[i - 1][0], STDIN_FILENO) == -1)
	{
		close(d.fd[i - 1][0]);
		close(d.fd[i][1]);
		free_fds(d.fd, d.nb_pipes);
		ft_perror("dup2", ERROR_CODE);
	}
	close(d.fd[i - 1][0]);
	if (dup2(d.fd[i][1], STDOUT_FILENO) == -1)
	{
		close(d.fd[i][1]);
		free_fds(d.fd, d.nb_pipes);
		ft_perror("dup2", ERROR_CODE);
	}
	close(d.fd[i][1]);
	free_fds(d.fd, d.nb_pipes);
	execute_command(d.env, (d.av)[i + d.is_hd + 2]);
}

static void	free_check_mid(t_pipex d)
{
	free_fds(d.fd, d.nb_pipes);
	check_children(d);
}

void	mid_parent(t_pipex d)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (++i < d.nb_pipes)
	{
		close((d.fd)[i - 1][1]);
		if (pipe(d.fd[i]) == -1)
		{
			free_check_mid(d);
			ft_perror("pipe", ERROR_CODE);
		}
		pid = fork();
		if (pid < 0)
		{
			close((d.fd)[i - 1][0]);
			free_check_mid(d);
			ft_perror("pid", ERROR_CODE);
		}
		if (pid == 0)
			mid_child(d, i);
		d.pid_last_child = pid;
		close((d.fd)[i - 1][0]);
	}
	close((d.fd)[i - 1][1]);
}
