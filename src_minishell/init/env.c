/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:13:23 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/03 14:29:14 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	original_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

char	**init_environnement(char **env)
{
	char	**envp;
	int		env_size;
	int		i;

	i = 0;
	env_size = original_env_size(env);
	envp = ft_calloc(sizeof(char *), env_size + 1);
	if (!envp)
		return (NULL);
	while (env[i])
	{
		if (env[i][0] == '_')
			envp[i] = ft_strdup("_=/usr/bin/env");
		else
			envp[i] = ft_strdup(env[i]);
		if (!envp[i])
			return (ft_free_double_ptr(&envp), NULL);
		i++;
	}
	return (envp);
}
