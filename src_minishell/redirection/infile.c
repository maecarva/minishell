/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:45:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 15:04:28 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	check_infile_access(t_pipes *p_data)
{
	if (access(p_data->name_infile, F_OK) == -1)
	{
		close(p_data->fd[0][1]);
		free_fd(&p_data->fd, p_data->nb_pipes);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(p_data->name_infile, 2);
		exit(EXIT_FAILURE);
	}
	if (access(p_data->name_infile, R_OK) == -1)
	{
		close(p_data->fd[0][1]);
		free_fd(&p_data->fd, p_data->nb_pipes);
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(p_data->name_infile, 2);
		exit(EXIT_FAILURE);
	}
}

static void	create_hd(t_pipes *p_data, char *limiter)
{
	char	*line;
	int		fd_infile;

	p_data->name_infile = "here_doc.tmp";
	fd_infile = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile == -1)
		ft_perror("open", ERROR_CODE);
	line = NULL;
	while (1)
	{
		if (get_next_line(0, &line) == -1 || !line)
		{
			ft_perror("malloc", ERROR_CODE);
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

void	get_infile(t_btree *cmd1, t_pipes *p_data)
{
	p_data->name_infile = NULL;
	while (cmd1->left != NULL)
	{
		if (p_data->is_hd == true)
		{
			if (unlink("here_doc.tmp") == -1)
				ft_perror("unlink", ERROR_CODE);
			p_data->is_hd = 0;
		}
		cmd1 = cmd1->left;
		if (((t_node2 *)(cmd1->item))->type == REDIRECT_INPUT)
		{
			p_data->name_infile = ((t_node2 *)(cmd1->item))->file;
			check_infile_access(p_data);
		}
		else if (((t_node2 *)(cmd1->item))->type == HEREDOC)
		{
			create_hd(p_data, ((t_node2 *)(cmd1->item))->file);
			p_data->is_hd = true;
		}
	}
}
