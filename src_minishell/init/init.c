/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:38:51 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/03 14:40:53 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	init_minishell(int ac, char **av, t_minishell *minishell)
{
	minishell->ac = ac;
	minishell->av = av;
	minishell->current_path = get_value_by_name(minishell->environnement, "PWD");
	if (minishell->current_path == NULL)
		return (INIT_ERROR);
	minishell->prompt = ft_strjoin(get_value_by_name(minishell->environnement, "LOGNAME"), " ~> \x1B[32mminishell #\x1B[37m ");
	if (minishell->prompt == NULL)
		return (INIT_ERROR);
	return (INIT_OK);
}

t_minishell	*init(int ac, char **av, char **env)
{
	t_minishell	*minishell;

	minishell = ft_calloc(sizeof(t_minishell), 1);
	if (!minishell)
		return (NULL);
	minishell->environnement = init_environnement(env);
	if (!minishell->environnement)
		return (clear_minishell(minishell), NULL);
	if (init_minishell(ac, av,minishell) == INIT_ERROR)
		return (clear_minishell(minishell), NULL);
	return (minishell);
}
