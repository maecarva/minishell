/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:41:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/18 16:00:10 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG 1

/* Libraries */

/* A definir */
// # include <readline/readline.h>

/* A definir */
// # include <readline/history.h>

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
/* A definir */
# include <readline/readline.h>

/* A definir */
# include <readline/history.h>

/* directory */
# include <dirent.h>

/* For stat */
#include <sys/stat.h>

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

# define MAX_PATH 2048

# define GETALLFILES 1
# define SEARCHFORFILES 2

# define NO_ENV_DEFAULT_SIZE 6

# define SHELL_NAME NULL
//"bash: "

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

// PARSING
/* Enumerate tokens */


typedef enum e_lexertok
{
	PIPE_TOKEN = 0,
	TRUNCATE = 1, // >
    APPEND = 2, // >>
    REDIRECT_INPUT = 3, // <
    HEREDOC = 4, // <<
	CMD = 5,
	ARGS = 6,
	FILE_ARG = 7,
	// builtin
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	OR,
	AND,
	PARENTHESIS_L,
	PARENTHESIS_R,
	ERROR,
	NONE
}	t_lexertok;

typedef struct s_lexertoklist
{
	char		*token;
	t_lexertok	type;
}	t_lexertoklist;


// /* Main structure */
// typedef	struct s_config {
// 	int		argc;
// 	char	**argv;
// 	char	**envp;
// 	t_list	*environnement; //////////////////////////////////////a changer en char **
// 	t_btree	*tree;
// 	char	*current_path;
// 	char	*prompt;
// 	int		last_error_code;
// }	t_config;
typedef	struct s_config {
	int		ac;
	char	**av;
	char	**environnement;
	char	*name_infile;
	char	*name_outfile;
	char	*current_path;
	char	*prompt;
	t_btree	*ast;
	t_btree	*dont_fucking_touch_me;
	int		last_error_code;
	char	*pidstr;
}	t_config;

/* Char constants */
# define PIPECHAR		'|'
# define R_LEFTCHAR		'<'
# define R_RIGHTCHAR	'>'
# define HERE_DOC		"<<"

# define SPECIALS_TOKEN	"|<>&()"
# define WHITESPACES	" \t\n\v\f\r"
# define EXPAND_CHARSET "$?\'\""



/* Prototypes */


typedef	struct	s_node2
{
	t_lexertok	type;
	char		*command;
	char		*file;
}	t_node2;

/******************************************************************************/
/*                                DEBUG_ONLY                                  */
/******************************************************************************/
# include <stdarg.h>

# define p(...) printf(__VA_ARGS__)
# include "pipes.h"

/******************************************************************************/
/*                                PROTOTYPES                                  */
/******************************************************************************/

/* Add your function prototypes here */

// init
t_config	*init(int ac, char **av, char **env);
int		clear_minishell(t_config *minishell);
// // env
char		**init_environnement(char **env);
char	*get_value_by_name(char **envp, char *name);
char	*get_var_ptr(char **envp, char *name);


/* Signals */
void	signals_interactive_mode(void);
void	signals_non_interactive_mode(void);


// temporary
t_btree	*arbre_bidon();

/*		PARSING		*/
bool	check_invalid_input(char *cmd);
t_btree	*parse_cmd2(char *cmd, t_config *config);
// lexer
bool	lexer(char *cmd, t_dlist **lexed_list);
void	free_token_list(t_dlist **dlist);
t_dlist	*spliter(char *cmd);
t_lexertoklist	*ptr_to_lexertoklist(void *token);
void	print_token_list(t_dlist **dlist);
void	handle_redirections(t_btree **node, t_dlist *start, t_dlist *end);
// expander
bool	expander(t_dlist *lexed_list, t_config *config);
void	expand_wildcards(char **cmd);
void	expand_token(char **tokenstr, char **envp, t_config *config);
void	clean_quotes(char *s);
// ast
bool	create_ast(t_btree **ast, t_dlist *tokenlist, t_config *config);
t_btree	*create_operator_node(t_lexertok type);
t_btree	*create_cmd_node(t_dlist *start, t_dlist *end);
void	free_ast(t_btree **ast);

// wildcards

int	tab_size(char **splited);
/*		END PARSING		*/
// ast


/* Builtin functions */

/* echo */
void	execute_pwd(char *cmd, t_config *minishell);
void	execute_env(char *cmd, t_config *minishell);
void	execute_exit(char *cmd, t_config *minishell);
void	execute_cd(char *cmd, t_config *minishell);
void	execute_unset(char *cmd, t_config *minishell);
char	**duplicate_env_without_var(char *varname, t_config *minishell);
void	execute_export(char *cmd, t_config *minishell);
void	execute_echo(char *cmd, t_config *minishell);

/* Free */
// void	free_minishell(t_config **ms_data);

/* Debuging */
void	print_arbre(t_btree *root, int level);

/* Others (en cours) */
void	execute_ast(t_btree *original_ast, t_config *ms_data);
// void	move_in_ast(t_config **ms_data);
void	check_type_execute(t_config *ms_data);

#endif /* MINISHELL_H */
