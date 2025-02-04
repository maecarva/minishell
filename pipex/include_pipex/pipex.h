/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:03:30 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/29 10:02:08 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

// For pid_t, 
# include <sys/types.h>

// For pipe(), read(), write(), close(), fork(), write()
# include <unistd.h>

// For exit(), free(), malloc()
# include <stdlib.h>

// For wait()
# include <sys/wait.h>

// For errno variable
# include <errno.h>

// For printf(), perror()
# include <stdio.h>

# include <fcntl.h>

# include "libft.h"
# include "get_next_line.h"

# define ERROR_CODE 42
# define ERROR_COMMAND 127

//pipex
typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**env;
	int		is_hd;
	char	*hd_content;
	int		option;
	int		nb_pipes;
	int		**fd;
	int		fd_infile;
	int		fd_outfile;
	int		pid_last_child;
}	t_pipex;

void	pipex(t_pipex data);

//pipex_init
int		**create_fds(int len);
t_pipex	init_pipex(int argc, char **argv, char **envp);

//first_parent
void	first_parent(t_pipex d);

//second_parent
void	last_parent(t_pipex *d);

//exec
void	execute_command(char **envp, char *cmd);

//pipex_init
void	free_fds(int **fd, int len);
int		**create_fds(int len);
t_pipex	init_pipex(int argc, char **argv, char **envp);

//pipex_utils
void	free_fds(int **fd, int len);
void	check_children(t_pipex data);

//here_doc
char	*obtain_hd_content(char *limiter);
void	fill_here_doc(t_pipex *d);
void	unlink_here_doc(t_pipex d);

#endif
