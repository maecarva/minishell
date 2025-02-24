/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:54:27 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/21 10:13:32 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

bool	is_valid_number(char *s)
{
	if (!s)
		return (false);
	if (*s == '\0')
		return (false);
	if (*s == '-' || *s == '+')
		s++;
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (false);
		s++;
	}
	return (true);
}

void	execute_exit(char **cmd, t_config *minishell)
{
	long	error_code;

	if (!cmd || !(*cmd) || !minishell)
		return ;
	// for (int i = 0; cmd[i] != NULL; i++) {
	// 	printf("cmd[%d] = [%s]\n", i, cmd[i]);
	// }
	if (tab_size(cmd) == 1)
	{
		minishell->last_error_code = 0;
		clear_minishell(minishell);
	}
	else if (tab_size(cmd) > 2 && !is_valid_number(cmd[1]))
	{
		ft_putstr_fd("exit: ", 2);
		error_message(SHELL_NAME, cmd[1], ": numeric argument required");
		minishell->last_error_code = 2;
		clear_minishell(minishell);
	}
	else if (tab_size(cmd) > 2)
	{
		error_message(SHELL_NAME, cmd[0], ": too many arguments");
		minishell->last_error_code = 1;
		clear_minishell(minishell);
	}
	else if (!is_valid_number(cmd[1]))
	{
		ft_putstr_fd("exit: ", 2);
		error_message(SHELL_NAME, cmd[1], ": numeric argument required");
		minishell->last_error_code = 2;
		clear_minishell(minishell);
	}
	error_code = ft_atol(cmd[1]) % 256;
	minishell->last_error_code = error_code;
	clear_minishell(minishell);
}
