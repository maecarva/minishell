/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rules2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:33:15 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 17:04:40 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

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

void	and_brain(char c, bool *sq, bool *dq, int *andcount)
{
	if (c == '\'' && *dq == false)
		*sq = !*sq;
	if (c == '\"' && *sq == false)
		*dq = !*dq;
	*andcount = 0;
}

void	parenthesis_brain(char c, int *state, int *parenthesis)
{
	if (c == '\'' && *state == 0)
		*state = 1;
	else if (c == '\'' && *state == 1)
		*state = 0;
	else if (c == '\"' && *state == 0)
		*state = 2;
	else if (c == '\"' && *state == 2)
		*state = 0;
	else if (c == '(' && *state == 0)
		(*parenthesis)++;
	else if (c == ')' && *state == 0)
		(*parenthesis)--;
}
