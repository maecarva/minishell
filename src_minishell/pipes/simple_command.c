/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:28:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 14:25:47 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	simple_child(t_pipes *p_data)
{
	if (dup2(p_data->fd_infile, STDIN_FILENO) == -1)
		ft_perror("dup2", ERROR_CODE);
	if (dup2(p_data->fd_outfile, STDOUT_FILENO) == -1)
		ft_perror("dup2", ERROR_CODE);
	execute_command(p_data->environnement, p_data->tree);
}

void	simple_command(t_pipes *p_data)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_perror("fork", ERROR_CODE);
	if (pid == 0)
		simple_child(p_data);
	p_data->pid_last_parent = pid;
}
