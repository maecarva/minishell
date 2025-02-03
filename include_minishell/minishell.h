/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:41:06 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 17:30:03 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/******************************************************************************/
/*                                LIBRARIES                                   */
/******************************************************************************/

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
# include "libft.h"        /* Custom library functions */
# include "get_next_line.h" /* GNL for reading lines */

/* Bool */
# include <stdbool.h>

/******************************************************************************/
/*                                CONSTANTS                                   */
/******************************************************************************/

# define ERROR_CODE 42      /* Generic error code */
# define ERROR_COMMAND 127  /* Command not found error code */

/******************************************************************************/
/*                                STRUCTURES                                  */
/******************************************************************************/

typedef struct s_minishell
{
	char	*filename;
	int		fd_infile;
	int		fd_outfile;
	char	*path_name;
}	t_minishell;

typedef struct s_command
{
	char	*command;
	char	*flags;
	t_list	*arguments;
	bool	quotes;  // quotes == 1 (true) for "" or blank and quotes == 0 (false) for ''
}	t_command;
/******************************************************************************/
/*                                PROTOTYPES                                  */
/******************************************************************************/

/* Add your function prototypes here */

#endif /* MINISHELL_H */
