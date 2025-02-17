/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:01 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/15 18:57:09 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

bool	is_special_token(t_lexertok type)
{
	if (type == PIPE_TOKEN || type == AND || type == OR)
		return (true);
	return (false);
}

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
				ft_putstr_fd("syntax error near unexpected token '", 2);
				ft_putchar_fd(ptr_to_lexertoklist(tmp->content)->token[0], 2);
				ft_putendl_fd("\'", 2);
				//printf("syntax error near unexpected token '%c'\n", ptr_to_lexertoklist(tmp->content)->token[0]);
				return (false);
			}
		}
		if (is_special_token(ptr_to_lexertoklist(tmp->content)->type) && is_special_token(ptr_to_lexertoklist(tmp->next->content)->type))
		{
				printf("Invalid token near : '%c'\n", ptr_to_lexertoklist(tmp->content)->token[0]);
				return (false);
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
