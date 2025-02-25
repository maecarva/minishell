/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:45:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/25 14:37:09 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static int	check_infile_access(t_pipes *p_data)
{
	if (access(p_data->name_infile, F_OK) == -1)
	{
		error_message(SHELL_NAME,
			p_data->name_infile, ": No such file or directory");
		ft_close(&p_data->to_close_one);
		ft_close(&p_data->to_close_two);
		free_fd(&p_data->fd, p_data->nb_pipes);
		p_data->ms_data->last_error_code = EXIT_FAILURE;
		return (1);
	}
	if (access(p_data->name_infile, R_OK) == -1)
	{
		error_message(SHELL_NAME, p_data->name_infile, ": Permission denied");
		ft_close(&p_data->to_close_one);
		ft_close(&p_data->to_close_two);
		free_fd(&p_data->fd, p_data->nb_pipes);
		p_data->ms_data->last_error_code = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

int	get_infile(t_pipes *p_data, t_btree *cmd)
{
	if (((t_node2 *)(cmd->item))->type == REDIRECT_INPUT)
	{
		p_data->name_infile = ((t_node2 *)(cmd->item))->file;
		if (check_infile_access(p_data) == 1)
			return (1);
	}
	else if (((t_node2 *)(cmd->item))->type == HEREDOC)
	{	
		p_data->name_infile = ((t_node2 *)(cmd->item))->file;
		if (access(p_data->name_infile, F_OK | R_OK) != 0)
		{
			perror(p_data->name_infile);
			ft_close(&p_data->to_close_one);
			ft_close(&p_data->to_close_two);
			free_fd(&p_data->fd, p_data->nb_pipes);
			p_data->ms_data->last_error_code = EXIT_FAILURE;
			return (1);
		}
	}
	return (0);
}
