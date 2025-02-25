/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:27 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 17:13:47 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	print_err(char *cmd, t_config *minishell)
{
	int	i;

	if (!cmd || !minishell)
		return ;
	i = -1;
	ft_putstr_fd("export: `", STDERR_FILENO);
	while (cmd[++i] )
		ft_putchar_fd(cmd[i], STDERR_FILENO);
	ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
	minishell->last_error_code = 1;
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
		if (ft_strncmp(name, minishell->environnement[i], ft_strlen(name)) == 0 && minishell->environnement[i][ft_strlen(name)] == '=')
		{
			free(minishell->environnement[i]);
			minishell->environnement[i] = ft_str_three_join(name, "=", value);
			return (ft_free_double_ptr(&env));
		}
		else
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
}

// only alphanum + _

bool	is_valid_env_name(char *name)
{
	int	i;

	if (!name)
		return (false);
	if (name[0] == '\0')
		return (false);
	i = 0;
	if (ft_isdigit(name[i]))
		return (false);
	i++;
	while (name[i])
	{
		if (!ft_isalnum(name[i]))
		{
			if (name[i] != '_')
				return (false);
		}
		i++;
	}
	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			if (name[i] == '=')
				break;
			return (false);
		}
		i++;
	}
	return (true);
}

int find_min_index(char **env, int start)
{
    int min_index = start;
    int i = start;
    
    while (env[i])
    {
        if (ft_strcmp(env[min_index], env[i]) > 0)
            min_index = i;
        i++;
    }
    return (min_index);
}

void	print_sorted_env(char **env)
{
	int	n;
	int	i;
	int	j;
	bool	passed;

	n = tab_size(env) - 1;
	i = 0;
	while (i < n)
	{
		passed = false;
		printf("declare -x ");
		j = 0;
		while (env[i][j])
		{
			printf("%c", env[i][j]);
			if (env[i][j] == '=' && passed == false)
			{
				passed = true;
				printf("\"");
			}
			j++;
		}
		i++;
		printf("\"\n");
	}
}

void export_sort(t_config *minishell)
{
    int i;
    int min_index;
    char **env;
    char *tmp;
	int	n;

	n = tab_size(minishell->environnement);
    env = duplicate_env_without_var("", minishell);
	if (!env)
	{
		minishell->last_error_code = ERROR_CODE;
		clear_minishell(minishell);
	}
    i = 0;
    while (env[i])
    {
        min_index = find_min_index(env, i);
        if (min_index != i)
        {
            tmp = env[i];
            env[i] = env[min_index];
            env[min_index] = tmp;
        }
        i++;
    }
	print_sorted_env(env);
	ft_free_double_ptr(&env);
	minishell->last_error_code = 0;
}

void	execute_export(char **cmd, t_config *minishell)
{
	int		i;
	int		j;
	char	*tmp;
	char	*name;
	char	*value;

	if (!cmd || !cmd[0] || !minishell)
		return ;
	if (cmd[1] == NULL)
		return (export_sort(minishell));
	i = 1;
	while (cmd[i])
	{
		j = 0;
		if (cmd[i][0] == '-')
		{
			print_invalid_option("export: ", cmd[i]);
			minishell->last_error_code = 2;
			return ;
		}
		tmp = ft_strchr(cmd[i], '=');
		if (!tmp)
		{
			if (ft_isdigit(cmd[i][0]))
				return (print_err(cmd[i], minishell));
			i++;
			continue ;
		}
		j =  tmp - cmd[i];
		name = ft_substr(cmd[i], 0, j);
		if (!is_valid_env_name(name))
		{
			print_err(cmd[i], minishell);
			ft_free_simple_ptr(&name);
			i++;
			continue ;
		}
		value = ft_substr(cmd[i], j + 1, ft_strlen(&cmd[i][j + 1]));
		if (value)
		{
			clean_quotes(&value);
			add_to_env(name, value, minishell);
		}
		ft_free_simple_ptr(&name);
		ft_free_simple_ptr(&value);
		i++;
	}
}
