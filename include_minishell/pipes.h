#ifndef PIPEX_H
# define PIPEX_H

#include "minishell.h"

/* structure */

typedef struct s_pipes
{
	int		ac;
	char	**av;
	char	**env;
	int		nb_pipes;
	int		fd_infile;
	int		fd_outfile;
	int		pid_last_child;
}	t_pipes;

/* prototypes */

//pipes
void	pipes(t_btree *arbrebidon, char **envp);
void	first_parent(t_btree *arbrebidon, char **envp, int *fd);
void	last_parent(t_btree *arbrebidon, char **envp, int *fd);

//execute commands
void	execute_command(char **envp, t_btree *arbrebidon);

#endif
