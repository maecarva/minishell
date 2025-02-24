/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:45:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/24 12:27:52 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	check_infile_access(t_pipes *p_data)
{
	if (access(p_data->name_infile, F_OK) == -1)
	{
		error_message(SHELL_NAME, p_data->name_infile, ": No such file or directory");
		ft_close(&p_data->to_close_one);
		ft_close(&p_data->to_close_two);
		free_fd(&p_data->fd, p_data->nb_pipes);
		p_data->ms_data->last_error_code = EXIT_FAILURE;
		clear_minishell(p_data->ms_data);
	}
	if (access(p_data->name_infile, R_OK) == -1)
	{
		error_message(SHELL_NAME, p_data->name_infile, ": Permission denied");
		ft_close(&p_data->to_close_one);
		ft_close(&p_data->to_close_two);
		free_fd(&p_data->fd, p_data->nb_pipes);
		p_data->ms_data->last_error_code = EXIT_FAILURE;
		clear_minishell(p_data->ms_data);
	}
}

void	get_infile(t_pipes *p_data, t_btree *cmd)
{
	if (((t_node2 *)(cmd->item))->type == REDIRECT_INPUT)
	{
		p_data->name_infile = ((t_node2 *)(cmd->item))->file;
		check_infile_access(p_data);
	}
	else if (((t_node2 *)(cmd->item))->type == HEREDOC)
		p_data->name_infile = ((t_node2 *)(cmd->item))->file;
}
