/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:31:40 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 17:05:49 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

bool	check_redir(char *cmd, t_config *minishell)
{
	int		cmdlen;

	if (!cmd)
		return (false);
	cmdlen = ft_strlen(cmd) - 1;
	if (cmd[cmdlen] == '>' && cmd[cmdlen - 1] == '>')
	{
		if (cmdlen == 2)
		{
			minishell->last_error_code = 2;
			return (ft_putstr_fd(SYNTAX_OUT, STDERR_FILENO), true);
		}
		else if (ft_count_char_in_str(cmd, '>') > 2)
		{
			minishell->last_error_code = 2;
			return (ft_putstr_fd(SYNTAX_APPEND, STDERR_FILENO), true);
		}
	}
	if (cmd[cmdlen] == '<' || cmd[cmdlen] == '>')
	{
		minishell->last_error_code = 2;
		return (ft_putstr_fd(SYNTAX_NEWLINE, STDERR_FILENO), true);
	}
	return (false);
}

/*
 * bools[] == 0: pipe, 1: doublequotes
 */
bool	check_pipes(char *cmd)
{
	int		i;
	char	lastchar;
	bool	bools[2];

	if (!cmd)
		return (false);
	i = -1;
	lastchar = cmd[0];
	ft_bzero(bools, sizeof(bools));
	if (cmd[ft_strlen(cmd) - 1] == '|' || *cmd == '|')
		return (true);
	while (++i < (int)(ft_strlen(cmd) - 1))
	{
		if (cmd[i] == '\"')
			bools[1] = !bools[1];
		if (!ft_isspace(cmd[i]) && cmd[i] != '|')
			lastchar = cmd[i];
		if (cmd[i] == '|')
		{
			if ((lastchar == '>' || lastchar == '<') && bools[1] == false)
				return (true);
			bools[0] = !bools[0];
		}
	}
	return (false);
}

bool	check_and(char *cmd)
{
	int		i;
	int		andcount;
	bool	sq;
	bool	dq;

	if (!cmd)
		return (false);
	i = -1;
	sq = false;
	dq = false;
	if (cmd[ft_strlen(cmd)] == '&' || *cmd == '&')
		return (true);
	while (cmd[++i])
	{
		and_brain(cmd[i], &sq, &dq, &andcount);
		if (cmd[i] == '&' && sq == false && dq == false)
		{
			while (cmd[i + andcount] && cmd[i + andcount] == '&')
				andcount++;
			if (andcount != 2)
				return (true);
			i += andcount;
		}
	}
	return (false);
}

bool	check_parenthesis(char *cmd)
{
	int	state;
	int	i;
	int	parenthesis;

	if (!cmd)
		return (false);
	i = -1;
	parenthesis = 0;
	state = 0;
	while (cmd[++i])
		parenthesis_brain(cmd[i], &state, &parenthesis);
	if (parenthesis < 0)
		return (ft_putstr_fd(SYNTAX_PR, STDERR_FILENO), true);
	else if (parenthesis > 0)
		return (ft_putstr_fd(SYNTAX_PL, STDERR_FILENO), true);
	return (false);
}

bool	check_invalid_input(char *cmd, t_config *minishell)
{
	if (!cmd)
		return (false);
	if (is_only_whitespaces(cmd))
		return (true);
	if (check_quotes(cmd))
		return (ft_putstr_fd("Invalid quotes.\n", STDERR_FILENO), true);
	if (check_pipes(cmd))
		return (ft_putstr_fd(SYNTAX_PIPE, STDERR_FILENO), true);
	if (check_redir(cmd, minishell))
		return (true);
	if (check_and(cmd))
		return (ft_putstr_fd(SYNTAX_AND, STDERR_FILENO), true);
	if (check_parenthesis(cmd))
		return (true);
	return (false);
}
