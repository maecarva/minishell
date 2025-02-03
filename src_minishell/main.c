/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:05:52 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 14:19:03 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_minishell/minishell.h"

void	print_env(t_minishell *minishell)
{
	t_list		*tmp;

	tmp = minishell->environnement;
	while (tmp)
	{
		printf("%s=%s\n", ((t_envvar *)tmp->content)->name, ((t_envvar *)tmp->content)->value);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_minishell	*minishell;
	char	*cmd;

	minishell = init(ac, av, env);
	if (!minishell)
		return (1);
	while ((cmd = readline(minishell->prompt)) != NULL)
	{
		if (ft_strncmp("env", cmd, ft_strlen("env")) == 0)
			print_env(minishell);
		else if (ft_strncmp("exit", cmd, ft_strlen("exit")) == 0)
		{
			free(cmd);
			clear_minishell(minishell);
			exit(EXIT_SUCCESS);
		}
		else
			printf("%s\n", cmd);
		free(cmd);
	}
	clear_minishell(minishell);
	return (0);
}
