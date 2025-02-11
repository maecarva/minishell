/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 14:53:55 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	first_child(t_pipes *p_data)
{
	int	fd_infile;

	if (!p_data->name_infile)
		fd_infile = 0;
	else
	{
		fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (fd_infile == -1)
			perror("open");
	}
	close(p_data->fd[0][0]);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
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
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->left->item))->command;
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
	{
		get_infile(p_data->ms_data->ast->left, p_data);
		fprintf(stderr, "this_is_the_infile: %s\n", p_data->name_infile);
		first_child(p_data);
	}
}
