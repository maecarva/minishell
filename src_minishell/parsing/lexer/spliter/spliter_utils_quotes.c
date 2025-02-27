/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils_quotes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:00:55 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 19:00:57 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

// void	quote_brain(char *cmd, int *end, bool *quotes, char cquote)
// {
// 	if (cmd[*end] == '\'' && cquote == cmd[*end])
// 		quotes[0] = !quotes[0];
// 	if (cmd[*end] == '\"' && cquote == cmd[*end])
// 		quotes[1] = !quotes[1];
// }

void	quote_brain(char *cmd, int *end, bool *quotes)
{
	if (cmd[*end] == '\'')
		quotes[0] = !quotes[0];
	if (cmd[*end] == '\"')
		quotes[1] = !quotes[1];
}

bool	no_quotes(bool *quotes)
{
	return (quotes[0] == false && quotes[1] == false);
}

bool	check_end(bool *quotes, char *cmd, int *end)
{
	if (no_quotes(quotes) && (ft_isspace(cmd[*end])
			|| ft_is_in_charset(cmd[*end], SPECIALS_TOKEN)))
	{
		*end -= 1;
		return (true);
	}
	return (false);
}

// quotes[] 0: sq 1: dq
void	extract_quoted(char *cmd, int *i, int *start, int *end)
{
	bool	quotes[2];

	ft_bzero(quotes, sizeof(bool) * 2);
	if (cmd[*i] == '\"')
		quotes[1] = true;
	else if (cmd[*i] == '\'')
		quotes[0] = true;
	*start = *i;
	*end = *start + 1;
	while (cmd[*end])
	{
		quote_brain(cmd, end, quotes);
		if (check_end(quotes, cmd, end))
			break ;
		if (cmd[*end] == cmd[*i] && no_quotes(quotes)
			&& !ft_isalnum(cmd[*end + 1])
			&& !ft_is_in_charset(cmd[*end], "\'\""))
			break ;
		if (cmd[*end + 1] == '\0')
			break ;
		*end += 1;
	}
	*end += 1;
	*i = *end;
}
