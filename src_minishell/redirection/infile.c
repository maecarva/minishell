/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:45:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/15 17:43:44 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static int	check_infile_access(t_pipes *p_data)
{
	if (access(p_data->name_infile, F_OK) == -1)
	{
		error_message(SHELL_NAME, p_data->name_infile, ": No such file or directory");
		free_fd(&p_data->fd, p_data->nb_pipes);
		p_data->ms_data->last_error_code = EXIT_FAILURE;
		return (1);
	}
	if (access(p_data->name_infile, R_OK) == -1)
	{
		error_message(SHELL_NAME, p_data->name_infile, ": Permission denied");
		free_fd(&p_data->fd, p_data->nb_pipes);
		p_data->ms_data->last_error_code = EXIT_FAILURE;
		return (1);
	}
	return (0);
}

static void	create_hd(t_pipes *p_data, char *limiter)
{
	char	*line;
	int		fd_infile;

	p_data->name_infile = "here_doc.tmp";
	fd_infile = open("here_doc.tmp", O_WRONLY | O_CREAT, 0644);
	if (fd_infile == -1)
	{
		perror("open");
		free_fd(&(p_data->fd), p_data->nb_pipes);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	line = NULL;
	while (1)
	{
		if (get_next_line(0, &line) == -1)
		{
			perror("malloc");
			unlink_hd(p_data);
			free_fd(&(p_data->fd), p_data->nb_pipes);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
		if (ft_strncmp(line, limiter,
				ft_max(ft_strlen(limiter), ft_strlen(line))) == '\n')
		{
			free(line);
			close(fd_infile);
			return ;
		}
		ft_putstr_fd(line, fd_infile);
	}
}

int	get_infile(t_pipes *p_data)
{
	t_btree	*cmd1;

	cmd1 = p_data->ms_data->ast;
	while (cmd1->left != NULL)
	{
		cmd1 = cmd1->left;
		if (p_data->is_hd == true)
		{
			unlink_hd(p_data);
			p_data->is_hd = false;
		}
		if (((t_node2 *)(cmd1->item))->type == REDIRECT_INPUT)
		{
			p_data->name_infile = ((t_node2 *)(cmd1->item))->file;
			if (check_infile_access(p_data) == 1)
				return (1);
		}
		else if (((t_node2 *)(cmd1->item))->type == HEREDOC)
		{
			create_hd(p_data, ((t_node2 *)(cmd1->item))->file);
			p_data->is_hd = true;
		}
	}
	return (0);
}
