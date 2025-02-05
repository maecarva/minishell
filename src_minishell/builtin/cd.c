/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:16:59 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/05 13:51:12 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(t_minishell *ms_data, t_command cmd_data)
{
	char	*new_path_cmd;

	if (cmd_data.flags != NULL)
	{
		ft_putstr("cd: -", 2);
		ft_putstr(cmd_data.flags[0], 2);
		ft_putendl(": invalid option", 2);
		exit(2);
	}
	new_path_cmd = ft_strdup("");
	if (new_path_cmd)
	if (access(path_cmd, X_OK) == 0)
}
