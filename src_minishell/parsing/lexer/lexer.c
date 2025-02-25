/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:01 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 19:26:29 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

bool	is_special_token(t_lexertok type)
{
	if (type == PIPE_TOKEN || type == AND || type == OR)
		return (true);
	return (false);
}

bool	validate(t_dlist **splited, t_dlist *tmp,
			t_lexertok type, t_lexertok next_type)
{
	if (type == PARENTHESIS_L
		&& (type == PARENTHESIS_R || is_special_token(type)))
	{
		ft_putstr_fd("syntax error near unexpected token `('\n", 2);
		return (false);
	}
	if (type == PARENTHESIS_R
		&& next_type == PARENTHESIS_L && tmp->next != *splited)
	{
		ft_putstr_fd("syntax error near unexpected token `('\n", 2);
		return (false);
	}
	if (type == PARENTHESIS_L && next_type == PARENTHESIS_R)
	{
		ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
		return (false);
	}
	if (type == PARENTHESIS_R && tmp->next != *splited && next_type == CMD)
	{
		ft_putstr_fd("syntax error near unexpected token `)'\n", 2);
		return (false);
	}
	return (true);
}

bool	print_msg(char *msg, t_dlist *tmp)
{
	ft_putstr_fd(msg, 2);
	ft_putchar_fd(ptr_to_lexertoklist(tmp->content)->token[0], 2);
	ft_putendl_fd("\'", 2);
	return (false);
}

bool	valid_token_list(t_dlist **splited)
{
	t_dlist		*tmp;
	t_lexertok	type;
	t_lexertok	next_type;

	if (!(*splited))
		return (false);
	tmp = *splited;
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		next_type = ptr_to_lexertoklist(tmp->next->content)->type;
		if (type >= TRUNCATE && type <= HEREDOC)
			if (next_type != FILE_ARG)
				return (print_msg("syntax error near unexpected token '", tmp));
		if (is_special_token(type)
			&& (is_special_token(next_type) || tmp->next == *splited))
			return (print_msg("syntax error near unexpected token '", tmp));
		if (!validate(splited, tmp, type, next_type))
			return (false);
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
	if (!valid_token_list(lexed_list))
		return (free_token_list(lexed_list), false);
	return (true);
}
