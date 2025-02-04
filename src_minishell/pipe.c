/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 09:53:33 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 10:49:24 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_binary_tree(t_minishell ms_data)
{
	if (tree. == "PIPE")
		
}

void	redirect_infile()
{
	
}
void	pipex(t_pipex p_data)
{
	
}

void	pipex(t_pipex p_data)
{
	int		i;
	pid_t	pid;

	i = 0;
	while (++i < d.nb_pipes)
	{
		close((d.fd)[i - 1][1]);
		if (pipe(d.fd[i]) == -1)
		{
			free_check_mid(d);
			ft_perror("pipe", ERROR_CODE);
		}
		pid = fork();
		if (pid < 0)
		{
			close((d.fd)[i - 1][0]);
			free_check_mid(d);
			ft_perror("pid", ERROR_CODE);
		}
		if (pid == 0)
			mid_child(d, i);
		d.pid_last_child = pid;
		close((d.fd)[i - 1][0]);
	}
	close((d.fd)[i - 1][1]);
}
