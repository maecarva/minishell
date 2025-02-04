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

t_envvar	*add_env_var(char *name, char *value)
{
	t_envvar	*var;

	var = ft_calloc(sizeof(t_envvar), 1);
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}

int	extract_env_var(char *var, t_envvar **envvar)
{
	int	i;
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	name = ft_calloc(sizeof(char), i + 1);
	if (!(name))
		return (ENV_PARSING_ERROR);
	ft_strlcpy(name, var, i + 1);
	value = ft_strdup(var + i + 1);
	if (!(value))
		return (free(name), ENV_PARSING_ERROR);
	*envvar = add_env_var(name, value);
	if (!(*envvar))
		return (ENV_PARSING_ERROR);
	return (ENV_PARSING_OK);
}

t_list	*init_environnement(char **env)
{
	t_list		*env_list;
	t_envvar	*tmp;
	t_list		*tmpelem;

	env_list = NULL;
	tmp = NULL;
	tmpelem = NULL;
	while (*env)
	{
		if (extract_env_var(*env, &tmp))
			return (printf("Free list pls.\n"), NULL);
		tmpelem = ft_lstnew(tmp);
		if (!tmpelem)
			return (printf("Failed to create list elem\n"), NULL);
		ft_lstadd_back(&env_list, tmpelem);
		env++;
	}
	return (env_list);
}
