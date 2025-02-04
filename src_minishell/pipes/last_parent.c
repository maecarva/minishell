/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_parent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 12:37:29 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

static void	last_child(t_btree *arbrebidon, char **envp, int *fd)
{
	int	fd_outfile = 1;

	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		ft_perror("dup2", ERROR_CODE);
	}
	close(fd[0]);
	if (dup2(fd_outfile, STDOUT_FILENO) == -1)
	{
		ft_perror("dup2", ERROR_CODE);
	}
	fprintf(stderr, "right=%s\n", (char *)arbrebidon->right->item);
	execute_command(envp, arbrebidon->right);
}

void	last_parent(t_btree *arbrebidon, char **envp, int *fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		ft_perror("pid", ERROR_CODE);
	}
	if (pid == 0)
		last_child(arbrebidon, envp, fd);
}
