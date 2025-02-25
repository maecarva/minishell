/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 16:47:45 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/18 11:15:03 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"
#include <unistd.h>

char	**duplicate_env_without_var(char *varname, t_config *minishell)
{
	char	**env;
	int		i;
	int		j;
	int		new_size;
	size_t	len;

	if (!varname || !minishell)
		return (NULL);
	len = ft_strlen(varname);
	i = 0;
	new_size = 0;
	while (minishell->environnement[i])
	{
		if (!(ft_strncmp(minishell->environnement[i], varname, len) == 0
			&& minishell->environnement[i][len] == '='))
			new_size++;
		i++;
	}
	env = ft_calloc(new_size + 1, sizeof(char *));
	if (!env)
		return (NULL);
	i = 0;
	j = 0;
	while (minishell->environnement[i])
	{
		if (ft_strncmp(minishell->environnement[i], varname, len) == 0
			&& minishell->environnement[i][len] == '=')
		{
			i++;
			continue;
		}
		env[j] = ft_strdup(minishell->environnement[i]);
		j++;
		i++;
	}
	env[j] = NULL;
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

	if (!cmd  || !cmd[0] || !minishell)
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

