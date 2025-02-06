/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:09:58 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/06 14:03:44 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

#include "minishell.h"

/* structure */

/* prototypes */

//pipes
void	pipes(t_btree *tree, char **envp);
void	simple_command(t_pipes *p_data);
void	first_parent(t_pipes *p_data);
void	infinite_parent(t_pipes *p_data);
void	last_parent(t_pipes *p_data);
void	check_children(t_pipes *data);

//execute commands
void	execute_command(char **envp, t_btree *arbrebidon);

//pipes utilisation
void	init_p_data(t_pipes *p_data, t_btree *tree, char **envp);
void	free_fds(int **fd, int len);

#endif

