/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:10:04 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 12:45:54 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	check_children(void)
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
	}
}

void	pipes(t_btree *arbrebidon, char **envp)
{
	int	fd[2];
	first_parent(arbrebidon, envp, fd);
	last_parent(arbrebidon, envp, fd);
	check_children();
}
