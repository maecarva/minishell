/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:10:04 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/05 11:03:15 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

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

void	pipes(t_btree *tree, char **envp)
{
	t_pipes	p_data;

	init_p_data(&p_data, tree, envp);
	if (p_data.nb_pipes == 0)
		simple_command(&p_data);
	else
	{
		first_parent(&p_data);
		infinite_parent(&p_data);
		last_parent(&p_data);
	}
	check_children(&p_data);
}

