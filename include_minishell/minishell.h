/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:41:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 18:20:26 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Libraries */

/* A definir */
# include <readline/readline.h>

/* A definir */
# include <readline/history.h>

/* For pid_t */
# include <sys/types.h>

/* For wait(), waitpid() */
# include <sys/wait.h>

/* For pipe(), read(), write(), close(), fork() */
# include <unistd.h>

/* For exit(), free(), malloc() */
# include <stdlib.h>

/* For errno variable */
# include <errno.h>

/* For printf(), perror() */
# include <stdio.h>

/* For bool variables (true == 1 or false == 0)*/
# include <stdbool.h>

/* For open(), O_RDONLY, O_WRONLY, etc. */
# include <fcntl.h>

/* Our own libraries */

# include "../libs/libft/include_libft/libft.h"
# include "../libs/gnl/include_gnl/get_next_line.h"

/* Number constants */

/* For Errors that we cannot handle : malloc, open, ... */
# define ERROR_CODE 42

/* Invalid Command */
# define ERROR_COMMAND 127

/* ? */
# define ENV_PARSING_ERROR 1

/* ? */
# define ENV_PARSING_OK 0

/* ? */
# define INIT_ERROR 1

/* ? */
# define INIT_OK 0

/* Colors */

# define KNRM  "\x1B[0m"
# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"
# define KYEL  "\x1B[33m"
# define KBLU  "\x1B[34m"
# define KMAG  "\x1B[35m"
# define KCYN  "\x1B[36m"
# define KWHT  "\x1B[37m"

/* Structures */

/* ? */
typedef struct s_cmd
{
	char	*cmd;
	bool	quotes;
	bool	redirection;
	char	*input_file;
	char	*output_file;
	bool	here_doc;
	char	*identifier;
}	t_cmd;

/* ? */
typedef struct s_envvar
{
	char	*name;
	char	*value;
}	t_envvar;

/* Enumerate tokens */
typedef enum e_token
{
	PIPE, //
	R_LEFT, // <
	R_RIGHT, // >
	RR_LEFT, // <<
	RR_RIGHT, // >>
	COMMAND,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	STOP //;
}	t_token;

/* Node content */
typedef struct s_node
{
	t_token	type;
	t_cmd	*cmd;
} t_node;

/* Binary tree */
typedef struct s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	t_node			*item;
}	t_btree;

/* Main structure */
typedef	struct s_config {
	int		argc;
	char	**argv;
	char	**envp;
	t_list	*environnement; //////////////////////////////////////a changer en char **
	t_btree	*tree;
	char	*current_path;
	char	*prompt;
	int		last_error_code;
}	t_config;

/* Char constants */
# define PIPECHAR		'|'
# define R_LEFTCHAR		'<'
# define R_RIGHTCHAR	'>'
# define HERE_DOC		"<<"

# define SPECIALS_TOKEN	"|"
# define WHITESPACES	" \t\n\v\f\r"

/* Other headers */
# include "pipes.h"

/* Prototypes */

/* Initalization */
t_config	*init(int ac, char **av, char **env);
void		clear_minishell(t_config *minishell);

/* Environnement */
t_list		*init_environnement(char **env);
t_envvar	*ptr_to_envvar(void	*content);
char		*get_value_by_name(t_list *env, char *name);

/* Signals */
void	init_signals(void);
t_btree	*arbre_bidon();

/* Parsing */
t_btree	*parse_cmd(char *cmd);
t_btree	*ft_btree_create_node(void *item);

/* AST */
void	construct_ast(t_btree **ast, char **cmd_split, int cmd_len);
t_btree	*create_special_node(t_token nodetype);
t_btree	*create_command_node(char **cmd_split);
void	clear_ast(t_btree *ast);

/* Builtin functions */

/* echo */
void	echo(t_btree *tree, char **envp);

/* Free */
void	free_minishell(t_config **ms_data);

/* Debuging */
void	print_arbre(t_btree *root, int level);

/* Others (en cours) */
void	check_type_execute(t_config *ms_data);

#endif /* MINISHELL_H */
