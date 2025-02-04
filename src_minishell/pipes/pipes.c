/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:10:04 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 18:29:06 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

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

void	check_children(t_pipes *data)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = 1;
	while (pid > 0)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1 && errno != ECHILD)
			ft_perror("waitpid", ERROR_CODE);
		exit_code = WEXITSTATUS(status);
		if (exit_code == ERROR_CODE)
			exit(ERROR_CODE);
		if (pid == data->pid_last_parent)
		{
			if (exit_code == ERROR_COMMAND || exit_code == ERROR_CODE
				|| exit_code == EXIT_FAILURE)
				exit(exit_code);
		}
	}
}

int	**create_fds(int len)
{
	int	**fd;
	int	i;

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
	fprintf(stderr, "%d\n", p_data->nb_pipes);
	p_data->fd = create_fds(p_data->nb_pipes);
	p_data->fd_infile = 0;
	p_data->fd_outfile = 1;
	p_data->pid_last_parent = -1;
}

void	pipes(t_pipes *p_data)
{
	first_parent(p_data);
	infinite_parent(p_data);
	last_parent(p_data);
	check_children(p_data);
}
