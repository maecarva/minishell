/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:28:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 15:24:08 by ebonutto         ###   ########.fr       */
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
		fd_infile = open(p_data->name_infile, O_RDONLY, 0644);
	if (!p_data->name_outfile)
		fd_outfile = 1;
	else
		fd_outfile = open(p_data->name_outfile, p_data->flags, 0644);
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		free_minishell(&(p_data->ms_data));
		ft_perror("dup2", ERROR_CODE);
	}
	p_data->cmd = ((t_node2 *)(p_data->ms_data->ast->item))->command;
	execute_command(p_data);
}

void	simple_command(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		free_minishell(&(p_data->ms_data));
		ft_perror("fork", ERROR_CODE);
	}
	if (pid == 0)
	{
		get_infile(p_data->ms_data->ast, p_data);
		get_outfile(p_data->ms_data->ast, p_data);
		simple_child(p_data);
	}
	p_data->pid_last_parent = pid;
}
