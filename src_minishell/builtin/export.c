/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:27 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/21 15:45:50 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	print_err(char *cmd, t_config *minishell)
{
	int	i;

	if (!cmd || !minishell)
		return ;
	i = -1;
	ft_putstr_fd("bash: export: `", STDERR_FILENO);
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
	return (true);
}

/*void	execute_export(char *cmd, t_config *minishell)
{
	int		i;
	char	*name;
	int		j;
	int		quotestatus;
	char	*value;

	if (!cmd || !minishell)
		return ;
	i = 0;
	j = 0;
	quotestatus = 0;
	name = NULL;
	value = NULL;
	// p("%s\n", cmd);
	while (!ft_isspace(cmd[i]))
		i++;
	while (ft_isspace(cmd[i]))
		i++;
	while (cmd[i])
	{
		j = i;
		if (cmd[j] == '=')
		{	
			print_err("=", minishell);
			i++;
			continue ;
		}

		while (cmd[j] && cmd[j] != '=')
			j++;
		name = ft_substr(cmd, i, j - i);
		if (!name)
			break ;

		// p("name : [%s]\n", name);
		i = j;
		while (cmd[i] && cmd[i] != '=')
			i++;
		if (cmd[i] == '=')
			i++;
		j = i;
		while (cmd[j])
		{
			if (cmd[j] == '\'' && quotestatus == 0)
				quotestatus = 1;
			else if (cmd[j] == '\'' && quotestatus == 1)
				quotestatus = 0;
			else if (cmd[j] == '\"' && quotestatus == 0)
				quotestatus = 2;
			else if (cmd[j] == '\"' && quotestatus == 2)
				quotestatus = 0;
			if (ft_isspace(cmd[j]) && quotestatus == 0)
				break ;
			j++;
		}
		clean_quotes(name);
		if (!is_valid_env_name(name))
		{
			print_err(name, minishell);
			ft_free_simple_ptr(&name);
			i += j - i;
			continue ;
		}
		value = ft_substr(cmd, i, j - i);
		// p("value : [%s]\n", value);
		clean_quotes(value);	
		// p("value : [%s]\n", value);
		add_to_env(name, value, minishell);
		if (name)
			ft_free_simple_ptr(&name);
		if (value)
			ft_free_simple_ptr(&value);
		i += j - i;
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
	}
}*/

void	execute_export(char **cmd, t_config *minishell)
{
	int		i;
	int		j;
	char	*tmp;
	char	*name;
	char	*value;

	if (!cmd || !cmd[0] || !minishell)
		return ;
	i = 1;
	while (cmd[i])
	{
		tmp = ft_strchr(cmd[i], '=');
		if (!tmp)
		{
			print_err(cmd[i], minishell);
			i++;
			continue ;
		}
		j =  tmp - cmd[i];
		name = ft_substr(cmd[i], 0, j);
		// p("name : [%s]\n", name);
		if (!is_valid_env_name(name))
		{
			print_err(name, minishell);
			ft_free_simple_ptr(&name);
			i++;
			continue ;
		}
		value = ft_substr(cmd[i], j + 1, ft_strlen(&cmd[i][j + 1]));
		// p("value : [%s]\n", value);
		if (ft_strlen(value) != 0)
		{
			clean_quotes(&value);
			add_to_env(name, value, minishell);
		}
		ft_free_simple_ptr(&name);
		ft_free_simple_ptr(&value);
		i++;
	}
}
