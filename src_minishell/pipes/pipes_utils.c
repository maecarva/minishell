/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:42:12 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/05 10:34:59 by ebonutto         ###   ########.fr       */
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

static int	**create_fds(int len)
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
			free_fds(fd, i);
			return (0);
		}
		i++;
	}
	return (fd);
}

void	init_p_data(t_pipes *p_data, t_btree *tree, char **envp)
{
	p_data->environnement = envp;
	p_data->tree = tree;
	p_data->nb_pipes = count_pipes(tree);
	
	p_data->fd = create_fds(p_data->nb_pipes);
	p_data->fd_infile = 0;
	p_data->fd_outfile = 1;
	p_data->pid_last_parent = -1;
}

void	free_fds(int **fd, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free(fd[i]);
		i++;
	}
	free(fd);
}
