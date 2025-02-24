/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:27:35 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/18 11:09:22 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	execute_env(char **cmd, t_config *minishell)
{
	int	i;

	if (!cmd || !cmd[0] || !minishell)
		return ;
	if (tab_size(cmd) > 1)
		return (ft_putstr_fd("env: no arguments required.\n", STDERR_FILENO));
	i = 0;
	while (minishell->environnement[i])
	{
		printf("%s\n", minishell->environnement[i]);
		i++;
	}
	minishell->last_error_code = 0;
}
