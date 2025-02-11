/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:46:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/11 15:23:51 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	check_outfile_access(t_pipes *p_data, int fd_outfile, t_btree *cmdn)
{
	if (access(p_data->name_outfile, F_OK) == 0)
	{
		if (access(p_data->name_outfile, R_OK) == -1)
		{
			close(p_data->fd[0][1]);
			free_fd(&p_data->fd, p_data->nb_pipes);
			ft_putstr_fd("permission denied: ", 2);
			ft_putendl_fd(p_data->name_outfile, 2);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		fd_outfile = open(((t_node2 *)(cmdn->item))->file, p_data->flags, 0644);
		if (fd_outfile == -1)
			perror("open");
		close(fd_outfile);
	}
}

void	get_outfile(t_btree *cmdn, t_pipes *p_data)
{
	int	fd_outfile;

	fd_outfile = 0;
	p_data->name_outfile = NULL;
	
	while (((t_node2 *)(cmdn->item))->type == PIPE_TOKEN)
		cmdn = cmdn->right;
	while (cmdn->right != NULL)
	{
		cmdn = cmdn->right;
		p_data->name_outfile = ((t_node2 *)(cmdn->item))->file;
		if (((t_node2 *)(cmdn->item))->type == TRUNCATE)
			p_data->flags = O_WRONLY | O_CREAT | O_TRUNC;
		else if (((t_node2 *)(cmdn->item))->type == APPEND)
			p_data->flags = O_WRONLY | O_CREAT | O_APPEND;
		check_outfile_access(p_data, fd_outfile, cmdn);
	}
	
}
