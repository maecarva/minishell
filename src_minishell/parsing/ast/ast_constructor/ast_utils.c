/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:49:35 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 20:54:02 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

bool	multiple_and_or(t_dlist *start, t_dlist *end)
{
	int		and;
	int		or;
	t_dlist	*tmp;

	if (!start || !end)
		return (false);
	and = 0;
	or = 0;
	tmp = start;
	if (start == end)
		return (false);
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == AND)
			and++;
		else if (ptr_to_lexertoklist(tmp->content)->type == OR)
			or++;
		tmp = tmp->next;
		if (tmp == end)
			break ;
	}
	return (and > 0 && or > 0);
}

bool	list_contain_pipe(t_dlist *start, t_dlist *end, t_dlist **pipeelem)
{
	t_dlist	*tmp;

	if (!start)
		return (false);
	tmp = start;
	if (start == end)
		return (ptr_to_lexertoklist(start->content)->type == PIPE_TOKEN);
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == PIPE_TOKEN)
		{
			*pipeelem = tmp;
			return (true);
		}
		tmp = tmp->next;
		if (tmp == end)
			break ;
	}
	return (false);
}

bool	list_contain_operator(t_dlist *start, t_dlist *end)
{
	t_dlist		*tmp;
	t_lexertok	type;

	if (!start)
		return (false);
	tmp = start;
	type = ptr_to_lexertoklist(start->content)->type;
	if (start == end)
		return (type == OR || type == AND);
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == OR || type == AND)
			return (true);
		tmp = tmp->next;
		if (tmp == end)
			break ;
	}
	return (false);
}

bool	get_last_and_or(t_dlist *start, t_dlist *end, t_dlist **op)
{
	t_dlist		*tmp;
	t_lexertok	type;

	if (!start || !end)
		return (false);
	tmp = end;
	type = ptr_to_lexertoklist(tmp->content)->type;
	if (type == AND || type == OR)
	{
		*op = tmp;
		return (true);
	}
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == OR || type == AND)
		{
			*op = tmp;
			return (true);
		}
		tmp = tmp->prev;
		if (tmp == start)
			break ;
	}
	return (false);
}

bool	get_first_and_or(t_dlist *start, t_dlist *end, t_dlist **op)
{
	t_dlist		*tmp;
	t_lexertok	type;

	if (!start || !end)
		return (false);
	tmp = start;
	type = ptr_to_lexertoklist(tmp->content)->type;
	if (type == AND || type == OR)
	{
		*op = tmp;
		return (true);
	}
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == OR || type == AND)
		{
			*op = tmp;
			return (true);
		}
		tmp = tmp->next;
		if (tmp == start)
			break ;
	}
	return (false);
}
