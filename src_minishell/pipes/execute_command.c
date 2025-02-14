/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:29:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/14 17:28:36 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static char	*find_path_cmd(char **paths, char **cmds, t_pipes *p_data)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (paths[i])
	{
		path_cmd = ft_str_three_join(paths[i], "/", cmds[0]);
		if (!path_cmd)
		{
			perror("malloc");
			ft_free_double_ptr(&paths);
			ft_free_double_ptr(&cmds);
			p_data->ms_data->last_error_code = ERROR_CODE;
			clear_minishell(p_data->ms_data);
		}
		if (access(path_cmd, X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
		i++;
	}
	return (NULL);
}

static void	handle_no_path(char ***cmds, char **path_cmd, t_pipes *p_data, int i)
{
	char **paths;

	paths = ft_split(p_data->ms_data->environnement[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	*cmds = ft_split(p_data->cmd, ' ');
	if (!*cmds)
	{
		perror("malloc");
		ft_free_double_ptr(&paths);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	*path_cmd = find_path_cmd(paths, *cmds, p_data);
	if (!*path_cmd)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd((*cmds)[0], 2);
		ft_free_double_ptr(&paths);
		ft_free_double_ptr(cmds);
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
	ft_free_double_ptr(&paths);
}

static void	check_access(char ***cmds, char **path_cmd, t_pipes *p_data)
{
	if (access(*path_cmd, F_OK | X_OK) != 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(*path_cmd, 2);
		ft_free_double_ptr(cmds);
		ft_free_simple_ptr(path_cmd);
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
}

static void	handle_path(char ***cmds, char **path_cmd, t_pipes *p_data)
{
	int		size;
	char	*target;

	target = ft_strrchr(p_data->cmd, '/');
	if (!target)
		target = p_data->cmd;
	else
		target++;
	*cmds = ft_split(target, ' ');
	if (!*cmds)
	{
		perror("malloc");
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	target = ft_strchr(target, ' ');
	if (!target)
		size = ft_strlen(p_data->cmd);
	else
		size = target - p_data->cmd;

	*path_cmd = ft_calloc(sizeof(char), (size + 1));
	if (!*path_cmd)
	{
		perror("malloc");
		ft_free_double_ptr(cmds);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_strlcpy(*path_cmd, p_data->cmd, size + 1);
	check_access(cmds, path_cmd, p_data);
}

static void	check_builtin_execute(t_pipes *p_data)
{
	if (p_data->type == ECHO)
	{
		execute_echo(p_data->cmd, p_data->ms_data);
		p_data->ms_data->last_error_code = 0;
		clear_minishell(p_data->ms_data);
	}
	else if (p_data->type == PWD)
	{
		execute_pwd(p_data->cmd, p_data->ms_data);
		p_data->ms_data->last_error_code = 0;
		clear_minishell(p_data->ms_data);
	}
	else if (p_data->type == ENV)
	{
		execute_env(p_data->cmd, p_data->ms_data);
		p_data->ms_data->last_error_code = 0;
		clear_minishell(p_data->ms_data);
	}
	else if (p_data->type == EXIT)
	{
		execute_exit(p_data->cmd, p_data->ms_data);
		p_data->ms_data->last_error_code = 0;
		clear_minishell(p_data->ms_data);
	}
	else if (p_data->type == CD)
	{
		execute_cd(p_data->cmd, p_data->ms_data);
		p_data->ms_data->last_error_code = 0;
		clear_minishell(p_data->ms_data);
	}
}

void	execute_command(t_pipes *p_data)
{
	char	**cmds;
	char	*path_cmd;
	int		i;

	i = 0;
	check_builtin_execute(p_data);
	while (p_data->ms_data->environnement[i] != NULL
		&& ft_strncmp(p_data->ms_data->environnement[i], "PATH=", 5) != 0)
		i++;
	if (p_data->ms_data->environnement[i] == NULL
		|| p_data->ms_data->environnement[i][0] == '\0' || p_data->cmd[0] == '/' || p_data->cmd[0] == '.')
		handle_path(&cmds, &path_cmd, p_data);
	else
		handle_no_path(&cmds, &path_cmd, p_data, i);
	if (execve(path_cmd, cmds, p_data->ms_data->environnement) == -1)
	{
		perror("execve");
		ft_free_double_ptr(&cmds);
		ft_free_simple_ptr(&path_cmd);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
}
