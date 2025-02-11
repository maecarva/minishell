/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 15:23:31 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	last_child(t_pipes *p_data)
{
	int	fd_outfile;
	
	if (!p_data->name_outfile)
		fd_outfile = 1;
	else
	{
		fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (fd_outfile == -1)
			perror("petitprobleme");
	}
	if (dup2(p_data->fd[p_data->nb_pipes - 1][0], STDIN_FILENO) == -1)
	{
		close(p_data->fd[p_data->nb_pipes - 1][0]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	close(p_data->fd[p_data->nb_pipes - 1][0]);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->right->item))->command;
	execute_command(p_data);
}

void	last_parent(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		free_fd(&(p_data->fd), p_data->nb_pipes);
		free_minishell(&(p_data->ms_data));
		ft_perror("pid", ERROR_CODE);
	}
	if (pid == 0)
	{
		get_outfile(p_data->ms_data->ast->left, p_data);
		fprintf(stderr, "this_is_the_outfile: %s\n", p_data->name_outfile);
		last_child(p_data);
	}
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->pid_last_parent = pid;
}
