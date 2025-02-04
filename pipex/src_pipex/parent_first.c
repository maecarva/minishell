/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_first.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:12:14 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/29 13:16:41 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	check_access(t_pipex *d)
{
	if (access(d->av[1], F_OK) == -1)
	{
		close(d->fd[0][1]);
		free_fds(d->fd, d->nb_pipes);
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(d->av[1], 2);
		exit(EXIT_FAILURE);
	}
	if (access(d->av[1], R_OK) == -1)
	{
		close(d->fd[0][1]);
		free_fds(d->fd, d->nb_pipes);
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(d->av[1], 2);
		exit(EXIT_FAILURE);
	}
}

static void	open_infile(t_pipex *d)
{
	if (d->is_hd == 1)
	{
		fill_here_doc(d);
		d->fd_infile = open("here_doc.tmp", O_RDONLY);
		if (d->fd_infile == -1)
		{
			close(d->fd[0][1]);
			free_fds(d->fd, d->nb_pipes);
			ft_perror("open", ERROR_CODE);
		}
		return ;
	}
	check_access(d);
	d->fd_infile = open(d->av[1], O_RDONLY);
	if (d->fd_infile == -1)
	{
		close(d->fd[0][1]);
		free_fds(d->fd, d->nb_pipes);
		ft_perror("open", ERROR_CODE);
	}
}

static void	first_child(t_pipex d)
{
	close (d.fd[0][0]);
	open_infile(&d);
	if (dup2(d.fd_infile, STDIN_FILENO) == -1)
	{
		close(d.fd_infile);
		close(d.fd[0][1]);
		free_fds(d.fd, d.nb_pipes);
		unlink_here_doc(d);
		ft_perror("dup2", ERROR_CODE);
	}
	close(d.fd_infile);
	if (dup2(d.fd[0][1], STDOUT_FILENO) == -1)
	{
		close(d.fd[0][1]);
		free_fds(d.fd, d.nb_pipes);
		unlink_here_doc(d);
		ft_perror("dup2", ERROR_CODE);
	}
	close(d.fd[0][1]);
	free_fds(d.fd, d.nb_pipes);
	unlink_here_doc(d);
	execute_command(d.env, (d.av)[2 + d.is_hd]);
}

void	first_parent(t_pipex d)
{
	pid_t	pid;

	if (pipe(d.fd[0]) == -1)
	{
		ft_free_simple_ptr(&(d.hd_content));
		free_fds(d.fd, d.nb_pipes);
		ft_perror("pipe", ERROR_CODE);
	}
	pid = fork();
	if (pid < 0)
	{
		ft_free_simple_ptr(&(d.hd_content));
		close(d.fd[0][0]);
		close(d.fd[0][1]);
		free_fds(d.fd, d.nb_pipes);
		ft_perror("fork", ERROR_CODE);
	}
	if (pid == 0)
		first_child(d);
	ft_free_simple_ptr(&(d.hd_content));
}
