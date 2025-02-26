/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:32:56 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 18:42:48 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

bool	is_in_same_command(t_dlist **dlist)
{
	t_dlist	*current_node;

	current_node = (*dlist)->prev;
	if (current_node == (*dlist))
		return (false);
	while (1)
	{
		if (ptr_to_lexertoklist(current_node->content)->type == PIPE_TOKEN)
			return (false);
		if (ptr_to_lexertoklist(current_node->content)->type == CMD)
			return (true);
		if (current_node == *dlist)
			break ;
		current_node = current_node->prev;
	}
	return (false);
}

t_lexertok	get_type_special(char	*token)
{
	t_lexertok	type;

	type = ERROR;
	if (!token)
		return (type);
	if (token[0] == '|' && token[1] == '\0')
		type = PIPE_TOKEN;
	else if (token[0] == '|' && token[1] == '|')
		type = OR;
	else if (token[0] == '&' && token[1] == '&')
		type = AND;
	else if (token[0] == '<' && token[1] == '\0')
		type = REDIRECT_INPUT;
	else if (token[0] == '>' && token[1] == '\0')
		type = TRUNCATE;
	else if (token[0] == '>' && token[1] == '>')
		type = APPEND;
	else if (token[0] == '<' && token[1] == '<')
		type = HEREDOC;
	else if (token[0] == '(')
		type = PARENTHESIS_L;
	else if (token[0] == ')')
		type = PARENTHESIS_R;
	return (type);
}

t_lexertok	get_token_type(char *token, t_dlist **dlist)
{
	t_lexertoklist	*tmp;

	tmp = NULL;
	if (ft_is_in_charset(token[0], SPECIALS_TOKEN))
		return (get_type_special(token));
	else
	{
		if ((*dlist) && (*dlist)->prev)
		{
			tmp = ptr_to_lexertoklist((*dlist)->prev->content);
			if (tmp->type == CMD)
				return (ARGS);
			else if ((tmp->type >= TRUNCATE && tmp->type <= HEREDOC))
				return (FILE_ARG);
			else if (tmp->type >= ARGS
				&& tmp->type <= FILE_ARG && is_in_same_command(dlist))
				return (ARGS);
			else
				return (CMD);
		}
		else
			return (CMD);
	}
	return (ERROR);
}

bool	add_to_token_list(t_dlist **dlist, char *cmd, int start, int end)
{
	t_dlist			*new;
	t_lexertoklist	*token;

	new = NULL;
	token = ft_calloc(sizeof(t_lexertoklist), 1);
	if (!token)
		return (false);
	token->token = ft_calloc(sizeof(char), end + 1);
	if (!token->token)
		return (free(token), false);
	ft_strlcpy(token->token, &cmd[start], end + 1);
	token->type = get_token_type(token->token, dlist);
	new = dll_new(token);
	if (!new)
		return (free(token->token), free(token), false);
	*dlist = dll_add_back(dlist, new);
	return (true);
}
