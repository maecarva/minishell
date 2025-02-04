/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_last.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:12:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/29 16:27:30 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	define_option_check(t_pipex *d)
{
	if (access((d->av)[d->ac - 1], F_OK) == 0)
	{
		if (access((d->av)[d->ac - 1], R_OK) == -1)
		{
			close(d->fd[0][1]);
			free_fds(d->fd, d->nb_pipes);
			ft_putstr_fd("permission denied: ", 2);
			ft_putendl_fd((d->av)[d->ac - 1], 2);
			exit(EXIT_FAILURE);
		}
	}
	if (d->is_hd == 1)
		d->option = O_WRONLY | O_CREAT | O_APPEND;
	else
		d->option = O_WRONLY | O_CREAT | O_TRUNC;
}

static void	last_child(t_pipex d)
{
	define_option_check(&d);
	d.fd_outfile = open((d.av)[d.ac - 1], d.option, 0644);
	if (d.fd_outfile == -1)
	{
		close(d.fd[d.nb_pipes - 1][0]);
		free_fds(d.fd, d.nb_pipes);
		ft_perror("open", ERROR_CODE);
	}
	if (dup2((d.fd)[d.nb_pipes - 1][0], STDIN_FILENO) == -1)
	{
		close(d.fd_outfile);
		close((d.fd)[d.nb_pipes - 1][0]);
		free_fds(d.fd, d.nb_pipes);
		ft_perror("dup2", ERROR_CODE);
	}
	close((d.fd)[d.nb_pipes - 1][0]);
	if (dup2(d.fd_outfile, STDOUT_FILENO) == -1)
	{
		close(d.fd_outfile);
		free_fds(d.fd, d.nb_pipes);
		ft_perror("dup2", ERROR_CODE);
	}
	close(d.fd_outfile);
	free_fds(d.fd, d.nb_pipes);
	execute_command(d.env, (d.av)[d.ac - 2]);
}

void	last_parent(t_pipex *d)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close((d->fd)[d->nb_pipes - 1][0]);
		free_fds(d->fd, d->nb_pipes);
		ft_perror("pid", ERROR_CODE);
	}
	if (pid == 0)
		last_child(*d);
	d->pid_last_child = pid;
	close((d->fd)[d->nb_pipes - 1][0]);
	free_fds(d->fd, d->nb_pipes);
}
