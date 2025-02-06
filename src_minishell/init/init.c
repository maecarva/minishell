/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:38:51 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/06 14:12:25 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	init_config(int ac, char **av, t_config *minishell)
{
	minishell->argc = ac;
	minishell->argv = av;
	minishell->current_path = get_value_by_name(minishell->environnement, "PWD");
	if (minishell->current_path == NULL)
		return (INIT_ERROR);
	minishell->prompt = ft_strjoin(get_value_by_name(minishell->environnement, "LOGNAME"), " ~> \x1B[32mminishell #\x1B[37m ");
	if (minishell->prompt == NULL)
		return (INIT_ERROR);
	return (INIT_OK);
}

t_config	*init(int ac, char **av, char **env)
{
	t_config	*minishell;

	minishell = ft_calloc(sizeof(t_config), 1);
	if (!minishell)
		return (NULL);
	minishell->environnement = init_environnement(env);
	if (!minishell->environnement)
		return (clear_minishell(minishell), NULL);
	if (init_config(ac, av,minishell) == INIT_ERROR)
		return (clear_minishell(minishell), NULL);
	return (minishell);
}
