/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 09:31:40 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/18 16:43:40 by ebonutto         ###   ########.fr       */
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
		if (cmd[i] == '\'' && doubleq == false)
			single = !single;
		if (cmd[i] == '\"' && single == false)
			doubleq = !doubleq;
		i++;
	}
	if (single || doubleq)
		return (true);
	return (false);
}

bool	check_redir(char *cmd, t_config *minishell)
{
	int		cmdlen;
	// bool	
	
	if (!cmd)
		return (false);
	cmdlen = ft_strlen(cmd) - 1;
	if (cmd[cmdlen] == '>' && cmd[cmdlen - 1] == '>')
	{
		if (cmdlen == 2)
		{
			minishell->last_error_code = 2;
			return (ft_putstr_fd("bash: syntax error near unexpected token `>'\n", STDERR_FILENO), true);
		}
		else if (ft_count_char_in_str(cmd, '>') > 2)
		{
			minishell->last_error_code = 2;
			return (ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", STDERR_FILENO), true);
		}
	}
	if (cmd[cmdlen] == '<' || cmd[cmdlen] == '>')
	{
		minishell->last_error_code = 2;
		return (ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", STDERR_FILENO), true);
	}
	return (false);
}

bool	check_pipes(char *cmd) // peut etre pas 100%bon
{
	int	cmdlen;
	int	i;
	bool	pipe;
	char	lastchar;
	bool	dquoted;

	if (!cmd)
		return (false);
	i = -1;
	pipe = false;
	cmdlen = ft_strlen(cmd) - 1;
	lastchar = cmd[0];
	dquoted = false;
	if (cmd[cmdlen] == '|' || *cmd == '|')
		return (true);
	while (++i < cmdlen)
	{
		if (cmd[i] == '\"')
			dquoted = !dquoted;
		if (!ft_isspace(cmd[i]) && cmd[i] != '|')
			lastchar = cmd[i];
		if (cmd[i] == '|')
		{
			if ((lastchar == '>' || lastchar == '<') && dquoted == false)
				return (true);
			pipe = !pipe;
			while (i < cmdlen && ft_isspace(cmd[++i]))
				;
		}
	}
	return (false);
}

bool	check_and(char *cmd)
{
	int		i;
	int		cmdlen;
	int		andcount;
	bool	sq;
	bool	dq;

	if (!cmd)
		return (false);
	i = -1;
	cmdlen = ft_strlen(cmd);
	sq = false;
	dq = false;
	if (cmd[cmdlen] == '&' || *cmd == '&')
		return (true);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && dq == false)
			sq = !sq;
		if (cmd[i] == '\"' && sq == false)
			dq = !dq;
		andcount = 0;
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
	int	parentesis;

	if (!cmd)
		return (false);
	i = 0;
	parentesis = 0;
	state = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' && state == 0)
			state = 1;
		else if (cmd[i] == '\'' && state == 1)
			state = 0;
		else if (cmd[i] == '\"' && state == 0)
			state = 2;
		else if (cmd[i] == '\"' && state == 2)
			state = 0;
		else if (cmd[i] == '(' && state == 0)
			parentesis++;
		else if (cmd[i] == ')' && state == 0)
			parentesis--;
		i++;
	}
	if (parentesis < 0)
		return (ft_putstr_fd(" syntax error near unexpected token `)'\n", STDERR_FILENO), true);
	else if (parentesis > 0)
		return (ft_putstr_fd(" syntax error near unexpected token `('\n", STDERR_FILENO), true);
	return (false);

}
// return true if invalid input
bool	check_invalid_input(char *cmd, t_config *minishell)
{
	if (!cmd)
		return (false);
	// check whitespaces
	if (is_only_whitespaces(cmd))
		return (true);
	// check quotes
	if (check_quotes(cmd))
		return (ft_putstr_fd("Invalid quotes.\n", STDERR_FILENO), true);
	// check pipes
	if (check_pipes(cmd))
		return (ft_putstr_fd(" syntax error near unexpected token `|'\n", STDERR_FILENO), true);
	// check redir
	if (check_redir(cmd, minishell))
		return (true);
	if (check_and(cmd))
		return (ft_putstr_fd(" syntax error near unexpected token `&'\n", STDERR_FILENO), true);
	if (check_parenthesis(cmd))
		return (true);
	return (false);
}
