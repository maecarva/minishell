/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:11:42 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 14:33:23 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex	init_pipex_bonus(int argc, char **argv, char **envp)
{
	t_pipex	data;

	data.ac = argc;
	data.av = argv;
	data.env = envp;
	data.pid_last_child = 0;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		data.is_hd = 1;
		data.hd_content = obtain_hd_content(argv[2]);
	}
	else
	{
		data.is_hd = 0;
		data.hd_content = NULL;
	}
	data.nb_pipes = data.ac - 4 - data.is_hd;
	data.fd = create_fds(data.nb_pipes);
	if (!data.fd)
	{
		ft_free_simple_ptr(&(data.hd_content));
		ft_perror("malloc", ERROR_CODE);
	}
	return (data);
}
