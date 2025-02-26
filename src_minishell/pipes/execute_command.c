/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 11:29:18 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/26 13:57:28 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

/* || p_data->cmds[0][0] == '\0'*/

static void	get_good_message_one(t_pipes *p_data)
{
	if (p_data->cmds[0] == NULL)
	{
		p_data->ms_data->last_error_code = EXIT_SUCCESS;
		clear_minishell(p_data->ms_data);
	}
	else if (p_data->cmds[0][0] == '\0')
	{
		error_message(SHELL_NAME, p_data->cmds[0], ": command not found");
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
	else if (ft_str_is_only_charset(p_data->cmds[0], ".") == true)
	{
		error_message(SHELL_NAME, p_data->cmds[0], ": command not found");
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
}

static void	get_good_message_two(t_pipes *p_data)
{
	if (ft_strcmp(p_data->cmds[0], "./") == 0
		|| ft_strcmp(p_data->cmds[0], "../") == 0)
	{
		error_message(SHELL_NAME, p_data->cmds[0], ": Is a directory");
		p_data->ms_data->last_error_code = CFBNE;
		clear_minishell(p_data->ms_data);
	}
	else if (p_data->cmds[0][0] == '.'
			&& p_data->cmds[0][1] != '/' && p_data->cmds[0][1] != '.'
			&& p_data->cmds[0][1] != '\0')
	{
		error_message(SHELL_NAME, p_data->cmds[0], ": command not found");
		p_data->ms_data->last_error_code = ERROR_COMMAND;
		clear_minishell(p_data->ms_data);
	}
}

void	execute_command(t_pipes *p_data)
{
	char	*path_cmd;
	int		i;

	i = 0;
	get_good_message_one(p_data);
	get_good_message_two(p_data);
	if (execute_builtin(p_data) == 1)
		clear_minishell(p_data->ms_data);
	while (p_data->ms_data->environnement[i] != NULL
		&& ft_strncmp(p_data->ms_data->environnement[i], "PATH=", 5) != 0)
		i++;
	if (p_data->ms_data->environnement[i] == NULL
		|| p_data->ms_data->environnement[i][0] == '\0'
		|| p_data->cmds[0][0] == '/' || p_data->cmds[0][0] == '.')
		handle_path(&path_cmd, p_data);
	else
		handle_no_path(&path_cmd, p_data, i);
	if (execve(path_cmd, p_data->cmds, p_data->ms_data->environnement) == -1)
	{
		perror("execve");
		ft_free_simple_ptr(&path_cmd);
		p_data->ms_data->last_error_code = ERROR_CODE;
		clear_minishell(p_data->ms_data);
	}
}
