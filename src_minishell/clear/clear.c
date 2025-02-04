/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:11:09 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 11:09:20 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	clear_env(t_list	**env)
{
	t_list	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = (*env)->next;
		free(ptr_to_envvar((*env)->content)->name);
		free(ptr_to_envvar((*env)->content)->value);
		free((*env)->content);
		free(*env);
		*env = tmp;
	}
}

void	clear_minishell(t_config *minishell)
{
	if (!minishell)
		return ;
	if (minishell->prompt)
		free(minishell->prompt);
	clear_env(&minishell->environnement);
	free(minishell);
}
