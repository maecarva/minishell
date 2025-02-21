/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infinite_parent.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/21 13:01:38 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	mid_child(t_pipes *p_data, int i)
{
	if (!p_data->name_infile)
		p_data->fd_infile = p_data->fd[i - 1][0];
	else
	{
		p_data->fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (p_data->fd_infile == -1)
		{
			perror("open");
			ft_close(&p_data->fd[i - 1][0]);
			ft_close(&p_data->fd[i][1]);
			unlink_hd(p_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (!p_data->name_outfile)
		p_data->fd_outfile = p_data->fd[i][1];
	else
	{
		p_data->fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (p_data->fd_outfile == -1)
		{
			perror("open");
			ft_close(&p_data->fd_infile);
			ft_close(&p_data->fd[i - 1][0]);
			ft_close(&p_data->fd[i][1]);
			unlink_hd(p_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_close(&p_data->fd[i - 1][0]);
		ft_close(&p_data->fd[i][1]);
		ft_close(&p_data->fd_infile);
		ft_close(&p_data->fd_outfile);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(&p_data->fd[i - 1][0]);
	ft_close(&p_data->fd_infile);
	unlink_hd(p_data);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		ft_close(&p_data->fd[i][1]);
		ft_close(&p_data->fd_outfile);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(&p_data->fd[i][1]);
	ft_close(&p_data->fd_outfile);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
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
		{
			perror("pipe");
			ft_close(&(p_data->fd)[i - 1][0]);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
		pid = fork();
		if (pid < 0)
		{
			perror("pid");
			ft_close(&(p_data->fd)[i - 1][0]);
			ft_close(&(p_data->fd)[i][0]);
			ft_close(&(p_data->fd)[i][1]);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;           /// attendre les enfants
			clear_minishell(p_data->ms_data);
		}
		if (pid == 0)
		{
			ft_close(&p_data->fd[i][0]);
			p_data->to_close_one = (p_data->fd)[i - 1][0];
			p_data->to_close_two = (p_data->fd)[i][1];
			p_data->ms_data->ast = p_data->ms_data->ast->left;
			get_redirections(p_data);
			mid_child(p_data, i);
		}
		ft_close(&(p_data->fd)[i - 1][0]);
		i++;
	}
	ft_close(&(p_data->fd)[i - 1][1]);
}
