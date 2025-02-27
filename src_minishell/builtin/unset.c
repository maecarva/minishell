/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:47:45 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 22:10:09 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	new_env_size(char *varname, t_config *minishell)
{
	int		i;
	int		new_size;
	size_t	len;

	i = 0;
	new_size = 0;
	len = ft_strlen(varname);
	while (minishell->environnement[i])
	{
		if (!(ft_strncmp(minishell->environnement[i], varname, len) == 0
				&& minishell->environnement[i][len] == '='))
			new_size++;
		i++;
	}
	return (new_size);
}

void	populate_new_env(char *varname, t_config *minishell, char **env)
{
	int		i;
	int		j;
	size_t	len;

	i = 0;
	j = 0;
	len = ft_strlen(varname);
	while (minishell->environnement[i])
	{
		if (ft_strncmp(minishell->environnement[i], varname, len) == 0
			&& minishell->environnement[i][len] == '=')
		{
			i++;
			continue ;
		}
		env[j] = ft_strdup(minishell->environnement[i]);
		if (!env[j])
			return (ft_free_double_ptr(&env));
		j++;
		i++;
	}
	env[j] = NULL;
}

char	**duplicate_env_without_var(char *varname, t_config *minishell)
{
	char	**env;
	int		new_size;

	if (!varname || !minishell)
		return (NULL);
	new_size = new_env_size(varname, minishell);
	env = ft_calloc(new_size + 1, sizeof(char *));
	if (!env)
		return (NULL);
	populate_new_env(varname, minishell, env);
	return (env);
}

void	print_invalid_option(char *name, char *s)
{
	int	i;

	i = -1;
	ft_putstr_fd(name, STDERR_FILENO);
	while (++i < 2)
		ft_putchar_fd(s[i], STDERR_FILENO);
	ft_putstr_fd(" : invalid option\n", STDERR_FILENO);
}

void	execute_unset(char **cmd, t_config *minishell)
{
	int		i;
	char	**envdup;

	if (!cmd || !cmd[0] || !minishell)
		return ;
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			print_invalid_option("unset: ", cmd[i]);
			minishell->last_error_code = 2;
			return ;
		}
		envdup = duplicate_env_without_var(cmd[i], minishell);
		if (!envdup)
			break ;
		ft_free_double_ptr(&minishell->environnement);
		minishell->environnement = envdup;
		i++;
	}
	minishell->last_error_code = 0;
}
