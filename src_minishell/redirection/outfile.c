/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:46:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/25 11:33:52 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_outfile_access(t_pipes *p_data, t_btree *cmdn)
{
	if (access(p_data->name_outfile, F_OK) == 0)
	{
		if (access(p_data->name_outfile, R_OK) == -1)
		{
			error_message(NULL, p_data->name_outfile, ": Permission denied");
			ft_close(&p_data->to_close_one);
			ft_close(&p_data->to_close_two);
			free_fd(&p_data->fd, p_data->nb_pipes);
			p_data->ms_data->last_error_code = EXIT_FAILURE;
			return (1);
		}
	}
	p_data->fd_outfile = open(((t_node2 *)(cmdn->item))->file, p_data->flags,
			0644);
	if (p_data->fd_outfile == -1)
	{
		perror(((t_node2 *)(cmdn->item))->file);
		ft_close(&p_data->to_close_one);
		ft_close(&p_data->to_close_two);
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_close(&p_data->fd_outfile);
	return (0);
}

int	get_outfile(t_pipes *p_data, t_btree *cmd)
{
	p_data->name_outfile = ((t_node2 *)(cmd->item))->file;
	if (((t_node2 *)(cmd->item))->type == TRUNCATE)
		p_data->flags = O_WRONLY | O_CREAT | O_TRUNC;
	else if (((t_node2 *)(cmd->item))->type == APPEND)
		p_data->flags = O_WRONLY | O_CREAT | O_APPEND;
	if (check_outfile_access(p_data, cmd) == 1)
		return (1);
	return (0);
}

	// struct stat statbuf;

	// if (stat(p_data->name_outfile, &statbuf) == 0)
	// {
	// 	if (S_ISDIR(statbuf.st_mode))
	// 	{
	// 		error_message(SHELL_NAME, p_data->name_outfile, ": Is a directory");
	// 		unlink_hd(p_data);
	// 		free_fd(&p_data->fd, p_data->nb_pipes);
	// 		p_data->ms_data->last_error_code = ERROR_COMMAND;
	// 		clear_minishell(p_data->ms_data);
	// 	}
	// }
	// else
	// {
	// 	perror("stat");
	// 	unlink_hd(p_data);
	// 	free_fd(&p_data->fd, p_data->nb_pipes);
	// 	p_data->ms_data->last_error_code = ERROR_CODE;
	// 	clear_minishell(p_data->ms_data);
	// }
