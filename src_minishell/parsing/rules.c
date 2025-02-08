/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:31:40 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/07 17:14:58 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

bool	is_only_whitespaces(char *cmd)
{
	int	i;

	if (!cmd)
		return (false);
	i = 0;
	while (cmd[i])
	{
		if (!ft_isspace(cmd[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	check_quotes(char *cmd)
{
	bool	single;
	bool	doubleq;
	int		i;

	if (!cmd)
		return (false);
	single = false;
	doubleq = false;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			single = !single;
		if (cmd[i] == '"')
			doubleq = !doubleq;
		i++;
	}
	if (single || doubleq)
		return (true);
	return (false);
}

bool	check_redir(char *cmd)
{
	int		cmdlen;
	
	if (!cmd)
		return (false);
	cmdlen = ft_strlen(cmd) - 1;
	if (cmd[cmdlen] == '<' || cmd[cmdlen] == '>')
		return (true);
	return (false);
}

bool	check_pipes(char *cmd) // peut etre pas 100%bon
{
	int	cmdlen;
	int	i;
	bool	pipe;

	if (!cmd)
		return (false);
	i = -1;
	pipe = false;
	cmdlen = ft_strlen(cmd) - 1;
	if (cmd[cmdlen] == '|' || *cmd == '|')
		return (true);
	while (++i < cmdlen)
	{
		if (cmd[i] == '|')
		{
				pipe = !pipe;
			while (i < cmdlen && ft_isspace(cmd[++i]))
				;
		}
		if (cmd[i] == '|' && pipe)
			return (true);
	}
	return (false);
}

// return true if invalid input
bool	check_invalid_input(char *cmd)
{
	if (!cmd)
		return (false);
	// check whitespaces
	if (is_only_whitespaces(cmd))
		return (true);
	// check quotes
	if (check_quotes(cmd))
		return (printf("Invalid quotes.\n"), true);
	// check redir
	if (check_redir(cmd))
		return (printf("Invalid redirection.\n"), true);
	// check pipes
	if (check_pipes(cmd))
		return (printf("Invalid pipes\n"), true);
	return (false);
}
