/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 15:48:20 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	get_io_mid(t_pipes *p_data, int i)
{
	if (!p_data->name_infile)
		p_data->fd_infile = p_data->fd[i - 1][0];
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
			clean_exit("open", p_data, p_data->fd[i - 1][0], p_data->fd[i][1]);
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = p_data->fd[i][1];
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (p_data->fd_outfile == -1)
		{
			ft_close(&p_data->fd_infile);
			clean_exit("open", p_data, p_data->fd[i - 1][0], p_data->fd[i][1]);
		}
	}
}

static void	mid_child(t_pipes *p_data, int i)
{
	get_io_mid(p_data, i);
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		ft_close(&p_data->fd_infile);
		ft_close(&p_data->fd_outfile);
		clean_exit("open", p_data, p_data->fd[i - 1][0], p_data->fd[i][1]);
	}
	ft_close(&p_data->fd[i - 1][0]);
	ft_close(&p_data->fd_infile);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
		clean_exit("dup2", p_data, p_data->fd[i][1], p_data->fd_outfile);
	ft_close(&p_data->fd[i][1]);
	ft_close(&p_data->fd_outfile);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmds = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
}

static void	get_child_info(t_pipes *p_data, int i)
{
	ft_close(&p_data->fd[i][0]);
	p_data->to_close_one = (p_data->fd)[i - 1][0];
	p_data->to_close_two = (p_data->fd)[i][1];
	p_data->ms_data->ast = p_data->ms_data->ast->left;
	if (get_redirections(p_data) == 1)
		clear_minishell(p_data->ms_data);
}

void	infinite_parent(t_pipes *p_data)
{
	int		i;
	pid_t	pid;

	i = 1;
	while (i < p_data->nb_pipes)
	{
		p_data->ms_data->ast = p_data->ms_data->ast->right;
		ft_close(&(p_data->fd)[i - 1][1]);
		if (pipe(p_data->fd[i]) == -1)
			clean_exit("pipe", p_data, (p_data->fd)[i - 1][0], -1);
		pid = fork();
		if (pid < 0)
		{
			ft_close(&(p_data->fd)[i - 1][0]);
			clean_exit("pid", p_data, (p_data->fd)[i][0], (p_data->fd)[i][1]);
		}
		if (pid == 0)
		{
			get_child_info(p_data, i);
			mid_child(p_data, i);
		}
		ft_close(&(p_data->fd)[i - 1][0]);
		i++;
	}
	ft_close(&(p_data->fd)[i - 1][1]);
}
