/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/25 11:19:56 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	last_child(t_pipes *p_data)
{
	if (!p_data->name_infile)
		p_data->fd_infile = p_data->fd[p_data->nb_pipes - 1][0];
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
		{
			perror("open");
			ft_close(&p_data->fd[p_data->nb_pipes - 1][0]);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = 1;
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (p_data->fd_outfile == -1)
		{
			perror("open");
			ft_close(&p_data->fd_infile);
			ft_close(&p_data->fd[p_data->nb_pipes - 1][0]);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_close(&p_data->fd[p_data->nb_pipes - 1][0]);
		ft_close(&p_data->fd_infile);
		ft_close(&p_data->fd_outfile);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(&p_data->fd[p_data->nb_pipes - 1][0]);
	ft_close(&p_data->fd_infile);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		ft_close(&p_data->fd_outfile);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(&p_data->fd_outfile);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmds = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
}

void	last_parent(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		ft_close(&p_data->fd[p_data->nb_pipes - 1][0]);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	if (pid == 0)
	{
		p_data->ms_data->ast =  p_data->ms_data->ast->right;
		p_data->to_close_one = p_data->fd[p_data->nb_pipes - 1][0];
		if (get_redirections(p_data) == 1)
			clear_minishell(p_data->ms_data);
		last_child(p_data);
	}
	ft_close(&p_data->fd[p_data->nb_pipes - 1][0]);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->pid_last_parent = pid;
}
