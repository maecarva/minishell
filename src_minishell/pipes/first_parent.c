/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 16:53:24 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

static void	first_child(t_pipes *p_data)
{
	close (p_data->fd[0][0]);
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		close(p_data->fd[0][1]);
		ft_perror("dup2", ERROR_CODE);
	}
	if (dup2(p_data->fd[0][1], STDOUT_FILENO) == -1)
	{
		close(p_data->fd[0][1]);
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[0][1]);
	execute_command(p_data->environnement, p_data->tree->left);
}

void	first_parent(t_pipes *p_data)
{
	pid_t	pid;

	if (pipe(p_data->fd[0]) == -1)
		ft_perror("pipe", ERROR_CODE);
	pid = fork();
	if (pid < 0)
	{
		close(p_data->fd[0][0]);
		close(p_data->fd[0][1]);
		ft_perror("fork", ERROR_CODE);
	}
	if (pid == 0)
		first_child(p_data);
}
