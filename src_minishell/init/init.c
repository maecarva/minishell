/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:38:51 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/03 11:45:51 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

t_list	*init_environnement(char **env)
{
	t_list	*env_list;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	return (NULL);
}

t_minishell	*init(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_minishell	*minishell;

	minishell = ft_calloc(sizeof(t_minishell), 1);
	if (!minishell)
		return (NULL);
	minishell->environnement = init_environnement(env);
	return (minishell);
}
