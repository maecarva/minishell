/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 21:55:21 by maecarva         ###   ########.fr       */
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
	minishell->last_error_code = 0;
}

void	cd(char **cmd, t_config *minishell, char *tmp)
{
	if (tab_size(cmd) >= 3)
		return (print_cd_errs(SHELL_NAME,
				"cd:", " too many arguments", minishell));
	else if (tab_size(cmd) == 1 || cmd[1][0] == '~'
			|| (cmd[1][0] == '-' && cmd[1][1] == '-'))
	{
		tmp = get_value_by_name(minishell->environnement, "HOME");
		if (chdir(tmp) == -1)
			return (print_cd_err("bash: cd: HOME not set\n",
					minishell), free(tmp));
	}
	else if (cmd[1][0] == '-')
	{
		tmp = get_value_by_name(minishell->environnement, "OLDPWD");
		if (chdir(tmp) == -1)
			return (print_cd_err("bash: cd: OLDPWD not set\n",
					minishell), free(tmp));
		else
			printf("%s\n", tmp);
	}
	else if (tab_size(cmd) > 1 && chdir(cmd[1]) == -1)
		return (print_cd_errs("bash: cd: ", cmd[1],
				": No such file or directory\n", minishell));
	return (clean_env_vars(minishell), free(tmp));
}

void	execute_cd(char **cmd, t_config *minishell)
{
	char	*tmp;

	if (!cmd || !minishell)
		return ;
	tmp = NULL;
	cd(cmd, minishell, tmp);
}
