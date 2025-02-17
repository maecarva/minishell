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
// a || b && c && d || e || f && g
void	construct(t_btree **ast, t_dlist *start, t_dlist *end, bool split3, int index)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (start == NULL || end == NULL)
		return ;
	tmp = NULL;
	tmp2 = NULL;
	if (list_contain_operator(start, end))
	{

	// printf("construct ast = %p start = %p end = %p split3 = %s, index = %d\n", *ast, start, end, split3 == true ? "true" : "false", index);
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
			// merde
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

void	finalise_ast(t_btree **ast)
{
	t_node2	*n;

	if (!(*ast))
		return ;
	n = (t_node2 *)((*ast)->item);
	if (n->type == CMD)
	{
		if (ft_strnstr(n->command, "echo", ft_strlen("echo")) == n->command)
			n->type = ECHO;
		else if (ft_strnstr(n->command, "cd", ft_strlen("cd")) == n->command)
			n->type = CD;
		else if (ft_strnstr(n->command, "pwd", ft_strlen("pwd")) == n->command)
			n->type = PWD;
		else if (ft_strnstr(n->command, "export", ft_strlen("export")) == n->command)
			n->type = EXPORT;
		else if (ft_strnstr(n->command, "unset", ft_strlen("unset")) == n->command)
			n->type = UNSET;
		else if (ft_strnstr(n->command, "env", ft_strlen("env")) == n->command)
			n->type = ENV;
		else if (ft_strnstr(n->command, "exit", ft_strlen("exit")) == n->command)
			n->type = EXIT;
	} 
	finalise_ast(&(*ast)->left);
	finalise_ast(&(*ast)->right);
}

bool	create_ast(t_btree **ast, t_dlist *tokenlist, t_config *config)
{
	if (!tokenlist || !config)
		return (false);
	construct(ast, tokenlist, tokenlist->prev, false, 0);
	// handle_redirections(ast, tokenlist, tokenlist->prev);
	finalise_ast(ast);
	return (true);
}
