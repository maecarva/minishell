/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 13:12:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/29 10:23:32 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*tmp_join(char *content, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(content, line);
	if (!tmp)
	{
		ft_free_simple_ptr(&content);
		ft_free_simple_ptr(&line);
		ft_perror("malloc", ERROR_CODE);
	}
	free(content);
	return (tmp);
}

char	*obtain_hd_content(char *limiter)
{
	char	*line;
	char	*content;

	line = NULL;
	content = ft_strdup("");
	if (!content)
		ft_perror("malloc", ERROR_CODE);
	while (1)
	{
		if (get_next_line(0, &line) == -1 || !line)
		{
			free(content);
			ft_free_simple_ptr(&content);
			ft_perror("malloc", ERROR_CODE);
		}
		if (ft_strncmp(line, limiter,
				ft_max(ft_strlen(limiter), ft_strlen(line))) == '\n')
		{
			free(line);
			return (content);
		}
		content = tmp_join(content, line);
	}
}

void	fill_here_doc(t_pipex *d)
{
	d->fd_infile = open("here_doc.tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (d->fd_infile == -1)
	{
		close(d->fd[0][1]);
		free_fds(d->fd, d->nb_pipes);
		ft_free_simple_ptr(&(d->hd_content));
		ft_perror("here_doc", ERROR_CODE);
	}
	if (d->hd_content)
		ft_putstr_fd(d->hd_content, d->fd_infile);
	ft_free_simple_ptr(&(d->hd_content));
	close(d->fd_infile);
}

void	unlink_here_doc(t_pipex d)
{
	if (d.is_hd == 1)
	{
		if (unlink("here_doc.tmp") == -1)
			ft_perror("unlink", ERROR_CODE);
	}
}
