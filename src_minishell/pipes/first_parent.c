/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 15:43:37 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_io_first(t_pipes *p_data)
{
	if (!p_data->name_infile)
		p_data->fd_infile = 0;
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
			clean_exit("open", p_data, p_data->fd[0][1], -1);
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = p_data->fd[0][1];
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (p_data->fd_outfile == -1)
			clean_exit("open", p_data, p_data->fd_infile, p_data->fd[0][1]);
	}
}

static void	first_child(t_pipes *p_data)
{
	get_io_first(p_data);
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		ft_close(&p_data->fd[0][1]);
		clean_exit("dup2", p_data, p_data->fd_infile, p_data->fd_outfile);
	}
	ft_close(&p_data->fd_infile);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
		clean_exit("dup2", p_data, p_data->fd[0][1], p_data->fd_outfile);
	ft_close(&p_data->fd[0][1]);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmds = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
}

void	first_parent(t_pipes *p_data)
{
	pid_t	pid;

	if (pipe(p_data->fd[0]) == -1)
	{
		perror("pipe");
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	pid = fork();
	if (pid < 0)
		clean_exit("fork", p_data, p_data->fd[0][0], p_data->fd[0][1]);
	if (pid == 0)
	{
		ft_close(&p_data->fd[0][0]);
		p_data->ms_data->ast = p_data->ms_data->ast->left;
		p_data->to_close_one = p_data->fd[0][0];
		if (get_redirections(p_data) == 1)
			clear_minishell(p_data->ms_data);
		first_child(p_data);
	}
}
