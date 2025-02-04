/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 18:28:17 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/30 14:46:39 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	check_children(t_pipex data)
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
		if (pid == data.pid_last_child)
		{
			if (exit_code == ERROR_COMMAND || exit_code == ERROR_CODE
				|| exit_code == EXIT_FAILURE)
				exit(exit_code);
		}
	}
	exit(EXIT_SUCCESS);
}
