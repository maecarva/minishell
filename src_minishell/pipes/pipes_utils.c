/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:42:12 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 18:17:37 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static int	count_pipes(t_btree	*arbre)
{
	int	count;

	if (!arbre)
		return (0);
	count = 0;
	while (arbre && ((t_node *)arbre->item)->type == PIPE)
	{
		count++;
		arbre = arbre->right;
	}
	return (count);
}

static int	**create_fd(int len)
{
	int	**fd;
	int	i;

	if (len == 0)
		return 0;
	fd = malloc(sizeof(int *) * (len));
	if (!fd)
		return (0);
	i = 0;
	while (i < len)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i])
		{
			free_fd(&fd, i);
			return (0);
		}
		i++;
	}
	return (fd);
}

void	init_p_data(t_pipes *p_data, t_config *ms_data)
{
	p_data->nb_pipes = count_pipes(ms_data->tree);
	p_data->fd = create_fd(p_data->nb_pipes);
	if (!p_data->fd)
		free_minishell(&ms_data);
	p_data->fd_infile = 0;
	p_data->fd_outfile = 1;
	p_data->pid_last_parent = -1;
	p_data->ms_data = ms_data;
}

void	free_fd(int ***fd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free((*fd)[i]);
		i++;
	}
	free(*fd);
	*fd = 0;
}
