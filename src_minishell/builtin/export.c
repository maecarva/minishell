/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:27 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/18 11:10:29 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

bool	valid_name(char *name)
{
	int	i;

	if (!name)
		return (false);
	i = -1;
	while (name[++i])
	{
		if (!ft_isalpha(name[i]) && (size_t)i < ft_strlen(name) - 1)
			return (false);
	}
	if (name[ft_strlen(name) - 1] != '+' && !ft_isalpha(name[ft_strlen(name) - 1]))
		return (false);
	return (true);
}

// bash: export: `C++++++++=test': not a valid identifier
void	print_err(char *cmd)
{
	int	i;

	if (!cmd)
		return ;
	i = -1;
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
	while (cmd[++i] )
		ft_putchar_fd(cmd[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
}

char	*get_varname(char *s, int start, int end)
{
	char	*name;

	if (!s)
		return (NULL);
	name = ft_calloc(end - start + 1, sizeof(char));
	if (!name)
		return (NULL);
	while (s[start] && start < end)
	{
		name[start] = s[start];
		start++;
	}
	return (name);
}

void	add_to_env(char *name, char *value, t_config *minishell)
{
	int		i;
	char	**env;

	if (!name || !value || !minishell)
		return ((void)free(value));
	i = 0;
	env = minishell->environnement;
	while (env[i])
		i++;
	env = ft_calloc(sizeof(char *), i + 2);
	if (!env)
		return ;
	i = 0;
	while (minishell->environnement[i])
	{
		env[i] = ft_strdup(minishell->environnement[i]);
		if (!env[i])
			return (ft_free_double_ptr(&env), (void)free(value));
		i++;
	}
	env[i] = ft_str_three_join(name, "=", value);
	if (!env[i])
		return (ft_free_double_ptr(&env), (void)free(value));
	env[++i] = NULL;
	ft_free_double_ptr(&minishell->environnement);
	minishell->environnement = env;
	free(value);
}

void	execute_export(char *cmd, t_config *minishell)
{
	int		i;
	char	*tmp;
	char	**splited;
	char	*name;
	char	*value;
	int		j;
	bool	error;

	j = 0;
	i = -1;
	tmp = NULL;
	splited = NULL;
	name = NULL;
	value = NULL;
	if (!cmd || !minishell)
		return ;
	splited = ft_split_charset(cmd, WHITESPACES);
	if (!splited)
		return ;
	while (splited[++i])
	{
		error = false;
		j = -1;
		while (splited[i] && ft_strchr(splited[i], '=') == NULL)
			i++;
		if (splited[i] == NULL)
			break ;
		while (splited[i][++j] && splited[i][j] != '=')
		{
			if (((splited[i][j] == '+' && splited[i][j + 1] == '+') || (splited[i][j] == '+' && splited[i][j + 1] != '=')))
			{
				print_err(splited[i]);
				error = true;
				break ;
			}
		}
		if (error == true)
			continue ;
		name = get_varname(splited[i], 0, j);
		if (!name || ft_strlen(name) == 0)
			continue ;
		if (valid_name(name) == false)
		{
			print_err(splited[i]);
			free(name);
			continue ;
		}
		if (name[ft_strlen(name) - 1] == '+') // add to existing
		{
			name[ft_strlen(name) - 1] = '\0';
			value = get_value_by_name(minishell->environnement, name);
			if (!value)
				add_to_env(name, ft_strdup(&splited[i][j + 1]), minishell);
			else
			{
				// danger si fail
				char	**tmpenv = duplicate_env_without_var(name, minishell);
				ft_free_double_ptr(&minishell->environnement);
				minishell->environnement = tmpenv;
				char	*tmp = ft_strdup(&splited[i][j + 1]);
				add_to_env(name, ft_strjoin(value, tmp ), minishell);
				free(tmp);
				free(value);
			}
		}
		else
		{
			char	**tmpenv = duplicate_env_without_var(name, minishell);
			ft_free_double_ptr(&minishell->environnement);
			minishell->environnement = tmpenv;
			add_to_env(name, ft_strdup(&splited[i][j + 1]), minishell);
		}
		free(name);
	}
	ft_free_double_ptr(&splited);
	minishell->last_error_code = 0;
}
