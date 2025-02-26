/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_no_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:55:40 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 13:22:31 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static char	*find_path_cmd(char **paths, t_pipes *p_data)
{
	int		i;
	char	*path_cmd;

	i = 0;
	while (paths[i])
	{
		path_cmd = ft_str_three_join(paths[i], "/", p_data->cmds[0]);
		if (!path_cmd)
		{
			perror("malloc");
			ft_free_double_ptr(&paths);
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

void	handle_no_path(char **path_cmd, t_pipes *p_data, int i)
{
	char	**paths;

	paths = ft_split(p_data->ms_data->environnement[i] + 5, ':');
	if (!paths)
	{
		perror("malloc");
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	if (ft_strchr(p_data->cmds[0], '/') != NULL
		&& access(p_data->cmds[0], F_OK) != 0)
	{
		error_message(NULL, p_data->cmds[0], ": No such file or directory");
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
	*path_cmd = find_path_cmd(paths, p_data);
	if (!*path_cmd)
	{
		error_message(SHELL_NAME, (p_data->cmds)[0], ": command not found");
		ft_free_double_ptr(&paths);
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
	ft_free_double_ptr(&paths);
}
