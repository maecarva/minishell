/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:28:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 15:40:55 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	simple_child(t_pipes *p_data)
{
	if (!p_data->name_infile)
		p_data->fd_infile = 0;
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
			clean_exit("open", p_data, -1, -1);
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = 1;
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (p_data->fd_outfile == -1)
			clean_exit("open", p_data, p_data->fd_infile, -1);
	}
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
		clean_exit("dup2", p_data, p_data->fd_infile, p_data->fd_outfile);
	ft_close(&p_data->fd_infile);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
		clean_exit("dup2", p_data, p_data->fd_outfile, -1);
	ft_close(&p_data->fd_outfile);
	p_data->cmds = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
}

//clean_exit(char *message, t_pipes *p_data, int c_one, int c_two);

static void	simple_parent(t_pipes *p_data)
{
	if (!p_data->name_infile)
		p_data->fd_infile = 0;
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
			clean_exit("open", p_data, -1, -1);
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = 1;
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (p_data->fd_outfile == -1)
			clean_exit("open", p_data, p_data->fd_infile, -1);
	}
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
		clean_exit("dup2", p_data, p_data->fd_infile, p_data->fd_outfile);
	ft_close(&p_data->fd_infile);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
		clean_exit("dup2", p_data, p_data->fd_outfile, -1);
	ft_close(&p_data->fd_outfile);
	p_data->cmds = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_builtin(p_data);
}

void	simple_command(t_pipes *p_data)
{
	pid_t	pid;

	if (((t_node2 *)(p_data->ms_data->ast->item))->type != CMD)
	{
		p_data->do_not_wait = true;
		if (get_redirections(p_data) == 1)
			return ;
		simple_parent(p_data);
		return ;
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		clear_minishell(p_data->ms_data);
		p_data->ms_data->last_error_code = ERROR_CODE;
	}
	if (pid == 0)
	{
		if (get_redirections(p_data) == 1)
			clear_minishell(p_data->ms_data);
		simple_child(p_data);
	}
	p_data->pid_last_parent = pid;
}
