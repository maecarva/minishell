/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 14:29:27 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 14:13:44 by ebonutto         ###   ########.fr       */
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
	while (cmd[++i])
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

bool	is_valid_env_name(char *name)
{
	int	i;

	if (!name || name[0] == '\0' || ft_isdigit(name[0]) == 1 || name[0] == '=')
		return (false);
	i = 0;
	while (name[i])
	{
		if (ft_isalnum(name[i]) == 0 && name[i] != '_')
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	export_loop(char *cmd, t_config *ms_data, char *tmp)
{
	int		is_plus;
	int		j;
	char	*name;
	char	*value;

	is_plus = 0;
	if (cmd[0] != '=' && *(tmp - 1) == '+')
		is_plus = 1;
	j = tmp - cmd - is_plus;
	name = ft_substr(cmd, 0, j);
	if (!name)
		clean_export(NULL, NULL, NULL, ms_data);
	if (!is_valid_env_name(name))
	{
		print_err(cmd, ms_data);
		ft_free_simple_ptr(&name);
		return ;
	}
	value = ft_substr(cmd, j + 1 + is_plus, ft_strlen(&cmd[j + 1]));
	if (!value)
		clean_export(NULL, NULL, name, ms_data);
	clean_quotes(&value);
	add_to_env(name, value, ms_data, is_plus);
	ft_free_simple_ptr(&name);
	ft_free_simple_ptr(&value);
}

void	execute_export(char **cmd, t_config *ms_data)
{
	int		i;
	char	*tmp;

	if (cmd[1] == NULL)
		return (export_sort(ms_data));
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			print_invalid_option("export: ", cmd[i]);
			ms_data->last_error_code = 2;
			return ;
		}
		tmp = ft_strchr(cmd[i], '=');
		if (!tmp)
		{
			if (!is_valid_env_name(cmd[i]))
				print_err(cmd[i], ms_data);
			i++;
			continue ;
		}
		export_loop(cmd[i], ms_data, tmp);
		i++;
	}
}
