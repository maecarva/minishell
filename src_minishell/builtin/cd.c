/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/24 14:12:27 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	tab_size(char **cmd)
{
	int	i;

	if (!cmd || !*cmd)
		return (0);
	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

void	clean_env_vars(t_config *minishell)
{
	char	*oldpwd;
	char	pwd[MAX_PATH];
	char	**cmd;

	cmd = ft_calloc(sizeof(char *), 3);
	if (!minishell)
		return ;
	ft_bzero(pwd, MAX_PATH);
	cmd[0] = ft_strdup("export");
	if (getcwd(pwd, MAX_PATH) == pwd)
	{
		oldpwd = get_value_by_name(minishell->environnement, "PWD");
		cmd[1] = ft_strjoin("OLDPWD=", oldpwd);
		execute_export(cmd, minishell);
		ft_free_simple_ptr(&oldpwd);
		ft_free_simple_ptr(&cmd[1]);
		cmd[1] = ft_strjoin("PWD=", pwd);
		execute_export(cmd, minishell);
		ft_free_double_ptr(&cmd);
	}
}

void	execute_cd(char **cmd, t_config *minishell)
{
	char	*tmp;

	if (!cmd || !minishell)
		return ;
	tmp = NULL;
	if (tab_size(cmd) >= 3)
	{
		minishell->last_error_code = 1;
		error_message(SHELL_NAME, "cd:", " too many arguments");
		return ;
	}
	else if (tab_size(cmd) == 1 || cmd[1][0] == '~' || (cmd[1][0] == '-' && cmd[1][1] == '-'))
	{
		tmp = get_value_by_name(minishell->environnement, "HOME");
		if (chdir(tmp) == -1)
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			minishell->last_error_code = 1;
			return ;
		}
	}
	else if (cmd[1][0] == '-')
	{
		tmp = get_value_by_name(minishell->environnement, "OLDPWD");
		if (chdir(tmp) == -1)
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			minishell->last_error_code = 1;
			return ;
		}
		else {
			printf("%s\n", tmp);
		}
	}
	else if (tab_size(cmd) > 1 && chdir(cmd[1]) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(cmd[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		minishell->last_error_code = 1;
		return ;
	}
	else
	{
		minishell->last_error_code = 0;
		clean_env_vars(minishell);
	}
	free(tmp);
}
