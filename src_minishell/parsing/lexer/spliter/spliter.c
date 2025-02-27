/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:01:37 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 19:15:24 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

void	get_special_token(char *cmd, t_dlist **splited, int *idxs)
{
	if (cmd[idxs[2]] == cmd[idxs[2] + 1]
		&& cmd[idxs[2]] != '(' && cmd[idxs[2]] != ')')
	{
		idxs[1] = idxs[2] + 2;
		add_to_token_list(splited, cmd, idxs[0], idxs[1] - idxs[0]);
		idxs[2] += 2;
	}
	else
	{
		idxs[1] = idxs[2] + 1;
		add_to_token_list(splited, cmd, idxs[0], idxs[1] - idxs[0]);
		idxs[2] += 1;
	}
}

void	get_quoted(char *cmd, t_dlist **splited, int *idxs)
{
	extract_quoted(cmd, &idxs[2], &idxs[0], &idxs[1]);
	add_to_token_list(splited, cmd, idxs[0], idxs[1] - idxs[0]);
}

void	get_general_case_token(char *cmd, t_dlist **splited,
					int *idxs, char cquote)
{
	while (cmd[idxs[2]] && !ft_isspace(cmd[idxs[2]])
		&& !ft_strchr(SPECIALS_TOKEN, cmd[idxs[2]]))
	{
		if (cmd[idxs[2]] == '\"' || cmd[idxs[2]] == '\'')
		{
			cquote = cmd[idxs[2]];
			idxs[2]++;
			if (cmd[idxs[2]] == cquote)
				idxs[2]++;
			else
				while (cmd[idxs[2]] && cmd[idxs[2]] != cquote)
					idxs[2]++;
			idxs[2]++;
		}
		else
			idxs[2]++;
	}
	idxs[1] = idxs[2];
	add_to_token_list(splited, cmd, idxs[0], idxs[1] - idxs[0]);
}

/*
 * idxs[] = 0: idxs[0], 1: idxs[1], 2: i
 * */
t_dlist	*spliter(char *cmd)
{
	t_dlist	*splited;
	int		idxs[3];
	char	cquote;

	if (!cmd)
		return (NULL);
	splited = NULL;
	idxs[2] = 0;
	cquote = 0;
	while (cmd[idxs[2]] != '\0')
	{
		while (cmd[idxs[2]] && ft_isspace(cmd[idxs[2]]))
			idxs[2]++;
		if (cmd[idxs[2]] == '\0')
			break ;
		idxs[0] = idxs[2];
		if (ft_strchr(SPECIALS_TOKEN, cmd[idxs[2]]))
			get_special_token(cmd, &splited, idxs);
		else if (cmd[idxs[2]] == '\"' || cmd[idxs[2]] == '\'')
			get_quoted(cmd, &splited, idxs);
		else
			get_general_case_token(cmd, &splited, idxs, cquote);
	}
	return (splited);
}
