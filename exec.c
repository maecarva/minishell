/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:00:49 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/03 17:24:40 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_built_in_command(t_minishell main_data, t_command data)
{
	if (ft_strcmp(data.command, "echo") == 0)
		execute_echo(data);
	else if (ft_strcmp(data.command, "cd") == 0)
		execute_cd(data);
	else if (ft_strcmp(data.command, "pwd") == 0)
		execute_pwd(data);
	else if (ft_strcmp(data.command, "export") == 0)
		execute_export(data);
	else if (ft_strcmp(data.command, "unset") == 0)
		execute_unset(data);
	else if (ft_strcmp(data.command, "env") == 0)
		execute_unset(data);
	else if (ft_strcmp(data.command, "exit") == 0)
		execute_unset(data);
	else
		execute_command(main_data, data);
}
