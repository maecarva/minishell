/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:41:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/30 18:05:34 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                                LIBRARIES                                   */
/******************************************************************************/

/* Read Command */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

/* Process and System Calls */
# include <sys/types.h>    /* For pid_t */
# include <sys/wait.h>     /* For wait() */
# include <unistd.h>       /* For pipe(), read(), write(), close(), fork() */

/* Memory Management */
# include <stdlib.h>       /* For exit(), free(), malloc() */

/* Error Handling */
# include <errno.h>        /* For errno variable */
# include <stdio.h>        /* For printf(), perror() */

/* File Operations */
# include <fcntl.h>        /* For open(), O_RDONLY, O_WRONLY, etc. */

/* Custom Libraries */
# include "../libs/libft/include_libft/libft.h"
// # include "../libs/gnl/include_gnl/get_next_line.h"

/******************************************************************************/
/*                                CONSTANTS                                   */
/******************************************************************************/

# define ERROR_CODE 42      /* Generic error code */
# define ERROR_COMMAND 127  /* Command not found error code */

/******************************************************************************/
/*                                STRUCTURES                                  */
/******************************************************************************/

/* Add your structures here */

typedef	struct s_minishell {
	t_list	*environnement;
	t_list	*env_commands;
	char	*current_path;
}	t_minishell;

/******************************************************************************/
/*                                PROTOTYPES                                  */
/******************************************************************************/

/* Add your function prototypes here */

t_minishell	*init(int ac, char **av, char **env);

#endif /* MINISHELL_H */
