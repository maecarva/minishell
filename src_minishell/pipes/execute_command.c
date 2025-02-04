/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:29:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/04 16:25:37 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

static char	*find_path_cmd(char **paths, char **cmds)
{
	int		i;
	char	*path_cmd;

	i = -1;
	while (paths[++i])
	{
		path_cmd = ft_str_three_join(paths[i], "/", cmds[0]);
		if (!path_cmd)
		{
			ft_free_double_ptr(&paths);
			ft_free_double_ptr(&cmds);
			ft_perror("malloc", ERROR_CODE);
		}
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
	}
	return (NULL);
}

static void	no_path(char ***cmds, char **path_cmd, char ***paths, char *cmd)
{
	*cmds = ft_split(cmd, ' ');
	if (!*cmds)
	{
		ft_free_double_ptr(paths);
		ft_perror("malloc", ERROR_CODE);
	}
	*path_cmd = find_path_cmd(*paths, *cmds);
	if (!*path_cmd)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd((*cmds)[0], 2);
		ft_free_double_ptr(paths);
		ft_free_double_ptr(cmds);
		exit(ERROR_COMMAND);
	}
	ft_free_double_ptr(paths);
}

void	execute_command(char **envp, t_btree *arbrebidon)
{
	char	**cmds;
	char	**paths;
	char	*path_cmd;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		ft_perror("malloc", ERROR_CODE);
	no_path(&cmds, &path_cmd, &paths, (char *)arbrebidon->item);
	if (execve(path_cmd, cmds, envp) == -1)
	{
		ft_free_double_ptr(&cmds);
		ft_free_simple_ptr(&path_cmd);
		ft_perror("execve", ERROR_CODE);
	}
}
