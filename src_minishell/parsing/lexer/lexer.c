/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:01 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/09 14:39:56 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

// false if invalid
// check if > < >> << is followed by FILE_ARG
bool	valid_token_list(t_dlist **splited)
{
	t_dlist	*tmp;

	if (!(*splited))
		return (false);
	tmp = *splited;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type >= TRUNCATE && ptr_to_lexertoklist(tmp->content)->type <= HEREDOC)
		{
			if (ptr_to_lexertoklist(tmp->next->content)->type != FILE_ARG)
			{
				printf("Invalid token near : '%c'\n", ptr_to_lexertoklist(tmp->content)->token[0]);
				return (false);
			}
		}
		tmp = tmp->next;
		if (tmp == *splited)
			break ;
	}
	return (true);
}

bool	lexer(char *cmd, t_dlist **lexed_list)
{
	if (!cmd)
		return (true);
	*lexed_list = spliter(cmd);
	if (!(*lexed_list))
		return (false);
	// print_token_list(lexed_list);
	if (!valid_token_list(lexed_list))
		return (free_token_list(lexed_list), false);
	return (true);
}
