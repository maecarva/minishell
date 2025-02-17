/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/17 17:45:43 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	first_child(t_pipes *p_data)
{
	close(p_data->fd[0][0]);
	if (!p_data->name_infile)
		p_data->fd_infile = 0;
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
		{
			perror("open");
			close(p_data->fd[0][1]);
			unlink_hd(p_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = p_data->fd[0][1];
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, O_RDONLY, 0644);
		if (p_data->fd_outfile == -1)
		{
			perror("open");
			close(p_data->fd[0][1]);
			unlink_hd(p_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(p_data->fd[0][1]);
		ft_close(p_data->fd_infile);
		unlink_hd(p_data);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(p_data->fd_infile);
	unlink_hd(p_data);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		close(p_data->fd[0][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	close(p_data->fd[0][1]);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
}

void	first_parent(t_pipes *p_data)
{
	pid_t	pid;

	if (pipe(p_data->fd[0]) == -1)
	{
		perror("pipe");
		unlink_hd(p_data);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE; 
		clear_minishell(p_data->ms_data);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		close(p_data->fd[0][0]);
		close(p_data->fd[0][1]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	if (pid == 0)
	{
		p_data->ms_data->ast = p_data->ms_data->ast->left;
		get_redirections(p_data);
		first_child(p_data);
	}
}
