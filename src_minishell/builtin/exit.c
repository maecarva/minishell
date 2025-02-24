/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 13:54:27 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/24 15:36:01 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

bool	is_valid_number(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (false);
	if (ft_islong(s) != true)
		return (false);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (s[i] == '\0')
		return (false);
	while (ft_isdigit(s[i]))
		i++;
	if (!(i != 0 && ft_isdigit(s[i - 1]) == 1))
		return (false);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] != '\0')
		return (false);
	return (true);
}

void	execute_exit(char **cmd, t_config *minishell)
{
	long	error_code;

	if (!cmd || !(*cmd) || !minishell)
		return ;
	if (tab_size(cmd) == 1)
	{
		minishell->last_error_code = 0;
		clear_minishell(minishell);
	}
	else if (tab_size(cmd) > 2)
	{
		if (!is_valid_number(cmd[1]))
		{
			error_message("exit: ", cmd[1], ": numeric argument required");
			minishell->last_error_code = 2;
			clear_minishell(minishell);
		}
		error_message(SHELL_NAME, cmd[0], ": too many arguments");
		minishell->last_error_code = 1;
		clear_minishell(minishell);
	}
	else if (is_valid_number(cmd[1]) == false)
	{
		error_message("exit: ", cmd[1], ": numeric argument required");
		minishell->last_error_code = 2;
		clear_minishell(minishell);
	}
	error_code = ft_atol(cmd[1]) % 256;
	minishell->last_error_code = error_code;
	clear_minishell(minishell);
}
