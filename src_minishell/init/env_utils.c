/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:38:45 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/15 17:40:07 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	get_name(char *name, char *var)
{
	int	i;

	if (!name || !var)
		return ;
	i = 0;
	while (var[i] && var[i] != '=' && i < MAX_PATH)
	{
		name[i] = var[i];
		i++;
	}
}

char	*get_value_by_name(char **envp, char *name)
{
	int		i;
	char	*value;
	char	*tmp;
	char	n[MAX_PATH];

	i = 0;
	value = NULL;
	tmp = NULL;
	if (!envp)
		return (NULL);
	if (ft_strlen(name) == 0)
		return (NULL);
	while (envp[i])
	{
		ft_bzero(n, MAX_PATH);
		get_name(n, envp[i]);
		if (n[0] != '\0')
		{
			if (ft_strncmp(n, name, ft_strlen(n)) == 0)
			{
				tmp = ft_strchr(envp[i], '=') + 1;
				if (!tmp)
					return (NULL);
				value = ft_strdup(tmp);
				if (!value)
					return (NULL);
				return (value);
			}
		}
		i++;
	}
	return (NULL);
}

char	*get_var_ptr(char **envp, char *name)
{
	int		i;
	char	*value;
	char	*tmp;
	char	n[MAX_PATH];

	i = 0;
	value = NULL;
	tmp = NULL;
	if (!envp)
		return (NULL);
	if (ft_strlen(name) == 0)
		return (NULL);
	while (envp[i])
	{
		ft_bzero(n, MAX_PATH);
		get_name(n, envp[i]);
		if (n[0] != '\0')
		{
			if (ft_strncmp(n, name, ft_strlen(n)) == 0)
			{
				return (envp[i]);
			}
		}
		i++;
	}
	return (NULL);
}
