/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:31:41 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/11 17:23:04 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

void	execute_pwd(char *cmd, t_config *minishell)
{
	char	path[MAX_PATH];

	ft_bzero(path, MAX_PATH);
	if (!cmd)
		return ;
	if (getcwd(path, MAX_PATH) != path)
		return (ft_putstr_fd("pwd: can't get current working directory.\n", STDERR_FILENO));
	printf("%s\n", path);
	minishell->last_error_code = 0;
}
