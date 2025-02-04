/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:51:10 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 13:12:10 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

t_pipex	init_pipex(int argc, char **argv, char **envp)
{
	t_pipex	data;

	data.ac = argc;
	data.av = argv;
	data.env = envp;
	data.pid_last_child = 0;
	data.is_hd = 0;
	data.hd_content = NULL;
	data.nb_pipes = data.ac - 4 - data.is_hd;
	data.fd = create_fds(data.nb_pipes);
	if (!data.fd)
	{
		ft_free_simple_ptr(&(data.hd_content));
		ft_perror("malloc", ERROR_CODE);
	}
	return (data);
}
