/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:27:55 by ebonutto          #+#    #+#             */
/*   Updated: 2025/01/28 13:11:19 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "pipex.h"

//pipex_bonus
void	pipex_bonus(t_pipex data);

//init
t_pipex	init_pipex_bonus(int argc, char **argv, char **envp);

//mid_parent
void	mid_parent(t_pipex d);

#endif
