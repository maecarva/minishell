/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 18:17:10 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

static void	last_child(t_pipes *p_data)
{
	if (dup2(p_data->fd[p_data->nb_pipes - 1][0], STDIN_FILENO) == -1)
	{
		close(p_data->fd[p_data->nb_pipes - 1][0]);
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[p_data->nb_pipes - 1][0]);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
	{
		ft_perror("dup2", ERROR_CODE);
	}
	execute_command(p_data->environnement, p_data->tree->right);
}

void	last_parent(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(p_data->fd[p_data->nb_pipes - 1][0]);
		ft_perror("pid", ERROR_CODE);
	}
	if (pid == 0)
		last_child(p_data);
	p_data->pid_last_parent = pid;
}
