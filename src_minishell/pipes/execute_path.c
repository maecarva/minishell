/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 12:52:34 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/27 13:27:50 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	access_path(char **path_cmd, t_pipes *p_data)
{
	if (access(*path_cmd, F_OK) != 0)
	{
		error_message(SHELL_NAME, *path_cmd, ": No such file or directory");
		ft_free_simple_ptr(path_cmd);
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
	if (access(*path_cmd, X_OK) != 0)
	{
		error_message(SHELL_NAME, *path_cmd, ": Permission denied");
		ft_free_simple_ptr(path_cmd);
		p_data->ms_data->last_error_code = CFBNE;
		clear_minishell(p_data->ms_data);
	}
}

static void	check_access(char **path_cmd, t_pipes *p_data)
{
	struct stat	statbuf;

	access_path(path_cmd, p_data);
	if (stat(*path_cmd, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
		{
			error_message(SHELL_NAME, *path_cmd, ": Is a directory");
			ft_free_simple_ptr(path_cmd);
			p_data->ms_data->last_error_code = IS_A_DIRECTORY;
			clear_minishell(p_data->ms_data);
		}
	}
	else
	{
		perror("stat");
		ft_free_simple_ptr(path_cmd);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
}

void	handle_path(char **path_cmd, t_pipes *p_data)
{
	int		size;

	size = ft_strlen(p_data->cmds[0]);
	*path_cmd = ft_calloc(sizeof(char), (size + 1));
	if (!*path_cmd)
	{
		perror("malloc");
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
	ft_strlcpy(*path_cmd, p_data->cmds[0], size + 1);
	ft_strcpy(p_data->cmds[0], ft_strrchr(p_data->cmds[0], '/') + 1);
	check_access(path_cmd, p_data);
}
