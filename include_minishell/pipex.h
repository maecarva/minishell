#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**env;
	int		nb_pipes;
	int		fd_infile;
	int		fd_outfile;
	int		pid_last_child;
}	t_pipex;

#endif
