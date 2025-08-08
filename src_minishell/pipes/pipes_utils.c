/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 09:42:12 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 15:21:07 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_pipes(t_btree	*arbre)
{
	int	count;

	if (!arbre)
		return (0);
	count = 0;
	while (arbre && ((t_node2 *)arbre->item)->type == PIPE_TOKEN)
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
		return (0);
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
	p_data->nb_pipes = count_pipes(ms_data->ast);
	if (p_data->nb_pipes > 0)
	{		
		p_data->fd = create_fd(p_data->nb_pipes);
		if (!p_data->fd)
		{
			perror("malloc");
			ms_data->last_error_code = ERROR_CODE;
			clear_minishell(ms_data);
		}
	}
	else
		p_data->fd = 0;
	p_data->do_not_wait = false;
	p_data->to_close_one = -1;
	p_data->to_close_two = -1;
	p_data->name_infile = NULL;
	p_data->name_outfile = NULL;
	p_data->pid_last_parent = -1;
	p_data->ms_data = ms_data;
}

void	free_fd(int ***fd, int len)
{
	int	i;

	if (len == 0)
		return ;
	i = 0;
	while (i < len)
	{
		free((*fd)[i]);
		i++;
	}
	free(*fd);
	*fd = 0;
}

void	clean_exit(char *message, t_pipes *p_data, int c_one, int c_two)
{
	perror(message);
	ft_close(&c_one);
	ft_close(&c_two);
	free_fd(&(p_data->fd), p_data->nb_pipes);
	p_data->ms_data->last_error_code = ERROR_CODE;
	clear_minishell(p_data->ms_data);
}
