/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:35:38 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/13 21:21:18 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

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

bool	get_last_and_or(t_dlist *start, t_dlist *end, t_dlist **operator)
{
	t_dlist		*tmp;
	t_lexertok	type;

	if (!start || !end)
		return (false);
	tmp = end;
	type = ptr_to_lexertoklist(tmp->content)->type;
	if (type == AND || type == OR)
	{
		*operator = tmp;
		return (true);
	}
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == OR || type == AND)
		{
			*operator = tmp;
			return (true);
		}
		tmp = tmp->prev;
		if (tmp == start)
			break ;
	}
	return (false);
}

bool	get_first_and_or(t_dlist *start, t_dlist *end, t_dlist **operator)
{
	t_dlist		*tmp;
	t_lexertok	type;

	if (!start || !end)
		return (false);
	tmp = start;
	type = ptr_to_lexertoklist(tmp->content)->type;
	if (type == AND || type == OR)
	{
		*operator = tmp;
		return (true);
	}
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == OR || type == AND)
		{
			*operator = tmp;
			return (true);
		}
		tmp = tmp->next;
		if (tmp == start)
			break ;
	}
	return (false);
}

bool	list_contain_parenthesis(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;

	if (!start || !end)
		return (false);
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_L || ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_R)
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

void	get_last_valid_operator(t_dlist *start, t_dlist *end, t_dlist **operator)
{
	int			parenthesis;
	t_dlist		*tmp;
	t_lexertok	type;

	if (!start || !end || !operator)
		return ;
	parenthesis = 0;
	tmp = end;
	while (tmp)
	{
		type = ptr_to_lexertoklist(tmp->content)->type;
		if (type == PARENTHESIS_L)
			parenthesis++;
		if (type == PARENTHESIS_R)
			parenthesis--;
		if (parenthesis == 0 && (type == AND || type == OR))
		{
			*operator = tmp;
			return ;
		}
		tmp = tmp->prev;
		if (tmp == start)
			break ;
	}
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
		if (ptr_to_lexertoklist(tmp->content)->type == PARENTHESIS_R && tmp == end && parenthesis == 0)
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

// premiere boucle a chier surement
void	get_first_valid_operator(t_dlist **start, t_dlist **end, t_dlist **operator)
{
	int			parenthesis;
	t_dlist		*tmp;
	t_lexertok	type;

	if (!*start || !*end || !operator)
		return ;
	parenthesis = 0;
	while (ptr_to_lexertoklist((*start)->content)->type == PARENTHESIS_L && ptr_to_lexertoklist((*end)->content)->type == PARENTHESIS_R)
	{
		if (*start == *end && (ptr_to_lexertoklist((*start)->content)->type == OR || ptr_to_lexertoklist((*start)->content)->type == AND))
			return ;
		if (ptr_to_lexertoklist((*start)->content)->type == PARENTHESIS_L && ptr_to_lexertoklist((*end)->content)->type == PARENTHESIS_R && same_parenthesis(*start, *end))
		{
			*start = (*start)->next;
			*end = (*end)->prev;
		}
		else 
			break ;
	}
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
			*operator = tmp;
			return ;
		}
		tmp = tmp->next;
		if (tmp == *end)
			break ;
	}
}
// a || b && c && d || e || f && g
void	construct(t_btree **ast, t_dlist *start, t_dlist *end, bool split3, int index)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (start == NULL || end == NULL)
		return ;
	tmp = NULL;
	tmp2 = NULL;

	// check && || neigbouring parenthesis
	if (list_contain_parenthesis(start, end) && list_contain_operator(start, end))
	{
		get_first_valid_operator(&start, &end, &tmp);
		if (tmp != NULL)
		{
			*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
			if (!ast)
				return ;
			construct(&(*ast)->left, start, tmp->prev, false, index);
			construct(&(*ast)->right, tmp->next, end, false, index);
		}
		else {
		get_last_and_or(start, end, &tmp);
		*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
		if (!*ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev, true, index + 1);
		construct(&(*ast)->right, tmp->next, end, false, index + 1);
		}
	}
	else if (list_contain_operator(start, end))
	{
		// check if only one type of operator
		if (multiple_and_or(start, end) == false)
		{
			get_first_and_or(start, end, &tmp);
			// create operator node
			*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
			if (!ast)
				return ;
			construct(&(*ast)->left, start, tmp->prev, false, index);
			construct(&(*ast)->right, tmp->next, end, false, index);
		}
		else {
			if (split3 == false)
			{
				get_last_and_or(start, end, &tmp);
				*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
				if (!*ast)
					return ;
				construct(&(*ast)->left, start, tmp->prev, true, index + 1);
				construct(&(*ast)->right, tmp->next, end, false, index + 1);
			}
			else
			{
				get_last_and_or(start, end, &tmp);
				if (!tmp)
					return ;
				get_last_and_or(start, tmp->prev, &tmp2);
				if (!tmp2)
					return ;
				*ast = create_operator_node(ptr_to_lexertoklist(tmp2->content)->type);
					
				construct(&(*ast)->left, start, tmp2->prev, true, index + 1);
				construct(&(*ast)->right, tmp2->next, end, false, index + 1);
			}
		}
	}
	else if (list_contain_pipe(start, end, &tmp))
	{
		// create pipe node
		*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
		if (!ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev, false, index + 1);
		construct(&(*ast)->right, tmp->next, end, false, index + 1);
	}
	else
	{
		// create command node
		*ast = create_cmd_node(start, end);
	}
}

void	finalise_ast(t_btree **ast, t_config *config)
{
	t_node2	*n;

	if (!(*ast))
		return ;
	n = (t_node2 *)((*ast)->item);
	if (n->type == CMD && n->command[0] != NULL)
	{
		if ((ft_strnstr(n->command[0], "echo", ft_strlen("echo")) == n->command[0]) && (n->command[0][4] == '\0'))
			n->type = ECHO;
		else if (ft_strnstr(n->command[0], "cd", ft_strlen("cd")) == n->command[0])
			n->type = CD;
		else if ((ft_strnstr(n->command[0], "pwd", ft_strlen("pwd")) == n->command[0]) && (n->command[0][3] == '\0'))
			n->type = PWD;
		else if (ft_strnstr(n->command[0], "export", ft_strlen("export")) == n->command[0])
			n->type = EXPORT;
		else if (ft_strnstr(n->command[0], "unset", ft_strlen("unset")) == n->command[0])
			n->type = UNSET;
		else if (ft_strnstr(n->command[0], "env", ft_strlen("env")) == n->command[0])
			n->type = ENV;
		else if (ft_strnstr(n->command[0], "exit", ft_strlen("exit")) == n->command[0])
			n->type = EXIT;
	}
	finalise_ast(&(*ast)->left, config);
	finalise_ast(&(*ast)->right, config);
}

bool	create_ast(t_btree **ast, t_dlist *tokenlist, t_config *config)
{
	if (!tokenlist || !config)
		return (false);
	construct(ast, tokenlist, tokenlist->prev, false, 0);
	finalise_ast(ast, config);
	return (true);
}
