/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:39:57 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 13:49:40 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_add_env(t_config *ms_data, char **env, char *name, char *value)
{
	int	i;

	i = 0;
	while (ms_data->environnement[i])
	{
		env[i] = ft_strdup(ms_data->environnement[i]);
		if (!env[i])
		{
			perror("secur");
		}
		i++;
	}
	env[i] = ft_str_three_join(name, "=", value);
	if (!env[i])
	{
		perror("secur");
	}
	ft_free_double_ptr(&(ms_data->environnement));
	ms_data->environnement = env;
}

static void	add_to_env_loop(t_config *ms_data, char *value, char *name, int i)
{
	char	*tmp;

	tmp = ms_data->environnement[i];
	ms_data->environnement[i] = ft_strjoin(ms_data->environnement[i], value);
	if (!ms_data->environnement[i])
		clean_export(tmp, name, value, ms_data);
	free(tmp);
}

void	add_to_env(char *name, char *value, t_config *ms_data, int is_plus)
{
	int		i;
	char	**env;

	i = 0;
	while (ms_data->environnement[i])
	{
		if (ft_strncmp(name, ms_data->environnement[i], ft_strlen(name)) == 0
			&& ms_data->environnement[i][ft_strlen(name)] == '=')
		{
			if (is_plus == 1)
				return (add_to_env_loop(ms_data, value, name, i));
			free(ms_data->environnement[i]);
			ms_data->environnement[i] = ft_str_three_join(name, "=", value);
			if (!ms_data->environnement[i])
				clean_export(NULL, name, value, ms_data);
			return ;
		}
		i++;
	}
	env = ft_calloc(sizeof(char *), i + 2);
	if (!env)
		clean_export(NULL, name, value, ms_data);
	copy_add_env(ms_data, env, name, value);
}
