/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:29:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/05 11:09:48 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

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

static void	check_access(char ***cmds, char **path_cmd)
{
	if (access(*path_cmd, F_OK | X_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(*path_cmd, 2);
		ft_free_double_ptr(cmds);
		ft_free_simple_ptr(path_cmd);
		exit(ERROR_COMMAND);
	}
}

static void	handle_path(char ***cmds, char **path_cmd, char *cmd)
{
	char	*last;
	int		d;

	last = ft_strrchr(cmd, '/');
	if (!last)
		last = cmd;
	else
		last++;
	*cmds = ft_split(last, ' ');
	if (!*cmds)
		ft_perror("malloc", ERROR_CODE);
	last = ft_strrchr(cmd, ' ');
	if (!last)
		d = ft_strlen(cmd);
	else
		d = last - cmd;
	*path_cmd = calloc(sizeof(char), (d + 1));
	if (!*path_cmd)
	{
		ft_free_double_ptr(cmds);
		ft_perror("malloc", ERROR_CODE);
	}
	ft_strlcpy(*path_cmd, cmd, d + 1);
	check_access(cmds, path_cmd);
}

void	execute_command(char **envp, t_btree *tree)
{
	char	**cmds;
	char	**paths;
	char	*path_cmd;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (envp[i] == NULL || envp[i][0] == '\0' || ((t_node *)(tree->item))->cmd->cmd[0] == '/' || ((t_node *)(tree->item))->cmd->cmd[0] == '.')
		handle_path(&cmds, &path_cmd, ((t_node *)(tree->item))->cmd->cmd);
	else
	{
		paths = ft_split(envp[i] + 5, ':');
		if (!paths)
			ft_perror("malloc", ERROR_CODE);
		no_path(&cmds, &path_cmd, &paths, ((t_node *)(tree->item))->cmd->cmd);
		ft_free_double_ptr(&paths);
	}
	if (execve(path_cmd, cmds, envp) == -1)
	{
		ft_free_double_ptr(&cmds);
		ft_free_simple_ptr(&path_cmd);
		ft_perror("execve", ERROR_CODE);
	}
}
