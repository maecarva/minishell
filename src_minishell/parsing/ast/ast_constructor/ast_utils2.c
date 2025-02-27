/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:55:07 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 21:30:33 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

bool	list_contain_parenthesis(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;

	if (!start || !end)
		return (false);
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_L
			|| ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_R)
		{
			if (tmp != start && tmp != end)
				return (true);
		}
		tmp = tmp->next;
		if (tmp == start)
			break ;
	}
	return (false);
}

bool	same_parenthesis(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;
	int		parenthesis;

	if (!start || !end)
		return (false);
	tmp = start;
	parenthesis = 0;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_R
			&& tmp == end && parenthesis == 0)
			return (true);
		if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_R)
			parenthesis--;
		else if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_L)
			parenthesis++;
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
	return (false);
}

void	clean_parenthesis(t_dlist **start, t_dlist **end)
{
	while (ptr_to_lexertoklist((*start)->content)->type == PARENTHESIS_L
		&& ptr_to_lexertoklist((*end)->content)->type == PARENTHESIS_R)
	{
		if (*start == *end
			&& (ptr_to_lexertoklist((*start)->content)->type == OR
				|| ptr_to_lexertoklist((*start)->content)->type == AND))
			return ;
		if (ptr_to_lexertoklist((*start)->content)->type == PARENTHESIS_L
			&& ptr_to_lexertoklist((*end)->content)->type == PARENTHESIS_R
			&& same_parenthesis(*start, *end))
		{
			*start = (*start)->next;
			*end = (*end)->prev;
		}
		else
			break ;
	}
}

void	get_first_valid_operator(t_dlist **start, t_dlist **end, t_dlist **op)
{
	int			parenthesis;
	t_dlist		*tmp;
	t_lexertok	type;

	if (!*start || !*end || !op)
		return ;
	parenthesis = 0;
	clean_parenthesis(start, end);
	tmp = *start;
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == PARENTHESIS_L)
			parenthesis++;
		if (type == PARENTHESIS_R)
			parenthesis--;
		if (parenthesis == 0 && (type == AND || type == OR))
		{
			*op = tmp;
			return ;
		}
		tmp = tmp->next;
		if (tmp == *end)
			break ;
	}
}
