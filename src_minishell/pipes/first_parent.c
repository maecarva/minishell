/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_parent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:17:02 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 12:35:32 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

static void	first_child(t_btree *arbrebidon, char **envp, int *fd)
{
	close (fd[0]);
	int	fd_infile = 0;
	if (dup2(fd_infile, STDIN_FILENO) == -1)
	{
		close(fd[1]);
		ft_perror("dup2", ERROR_CODE);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[1]);
		ft_perror("dup2", ERROR_CODE);
	}
	close(fd[1]);
	fprintf(stderr, "left=%s\n", (char *)arbrebidon->left->item);
	execute_command(envp, arbrebidon->left);
}

void	first_parent(t_btree *arbrebidon, char **envp, int *fd)
{
	pid_t	pid;

	if (pipe(fd) == -1)
		ft_perror("pipe", ERROR_CODE);
	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		ft_perror("fork", ERROR_CODE);
	}
	if (pid == 0)
		first_child(arbrebidon, envp, fd);
}
