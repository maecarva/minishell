/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:28:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/17 15:15:18 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	simple_child(t_pipes *p_data)
{
	int	fd_infile;
	int	fd_outfile;
	
	if (!p_data->name_infile)
		fd_infile = 0;
	else
	{
		fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
		if (fd_infile == -1)
		{
			perror("open");
			unlink_hd(p_data);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (!p_data->name_outfile)
		fd_outfile = 1;
	else
	{
		fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
		if (fd_outfile == -1)
		{
			perror("open");
			ft_close(fd_infile);
			unlink_hd(p_data);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
	}
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		perror("dup2");
		ft_close(fd_infile);
		ft_close(fd_outfile);
		unlink_hd(p_data);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(fd_infile);
	unlink_hd(p_data);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		ft_close(fd_outfile);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(fd_outfile);
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	p_data->type = ((t_node2 *)(p_data->ms_data->ast->item))->type;
	execute_command(p_data);
}

int	simple_command(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		unlink_hd(p_data);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	if (pid == 0)
	{
		get_redirections(p_data);
		simple_child(p_data);
	}
	unlink_hd(p_data);
	p_data->pid_last_parent = pid;
	return (0);
}
