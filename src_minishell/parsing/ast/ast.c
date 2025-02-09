/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:35:38 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/09 16:18:42 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	print_cmd_borned(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;
	p("CMD part : -------------------------------\n");

	tmp = start;
	while (tmp)
	{
		printf("token : [%s]\n", ptr_to_lexertoklist(tmp->content)->token);
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
}

bool	list_contain_pipe(t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;

	if (!start)
		return (false);
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == PIPE_TOKEN)
			return (true);
		if (tmp == start || tmp == end)
			break ;
		tmp = tmp->next;
	}
	return (false);
}

void	construct(t_btree **ast, t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;

	if (start == NULL || end == NULL)
		return ;
	if (list_contain_pipe(start, end))
	{
		// create pipe node
		tmp = start;
		if (ptr_to_lexertoklist(tmp->content)->type != PIPE_TOKEN)
			while (ptr_to_lexertoklist(tmp->content)->type != PIPE_TOKEN)
				tmp = tmp->next;
		*ast = create_pipe_node();
		if (!ast)
			return ;
		construct(&(*ast)->left, start, tmp);
		construct(&(*ast)->left, tmp->next, end);
	}
	else
	{
		// create command node
		*ast = create_cmd_node(start, end);
	}
}

// separate list to ditinguish cmd && pipes
bool	create_ast(t_btree **ast, t_dlist *tokenlist, t_config *config)
{
	// t_dlist	*start;
	// t_dlist	*end;
	// int		total_token;
	// int		token_treated;
	// p("Init ast creation.\n");
	construct(ast, tokenlist, tokenlist->prev);
	if (!tokenlist)
		return (false);
	// start = tokenlist;
	// end = start;
	// total_token = dll_size(&tokenlist);
	// token_treated = 0;
	// while (token_treated < total_token)
	// {
	// 	if (ptr_to_lexertoklist(end->content)->type == PIPE_TOKEN)
	// 	{
	// 		print_cmd_borned(end, end);
	// 		token_treated += dll_size_between(end, end);
	// 		start = end->next;
	// 	}
	// 	else 
	// 	{
	// 		start = end;
	// 		while (ptr_to_lexertoklist(end->next->content)->type != PIPE_TOKEN && end->next != tokenlist)
	// 			end = end->next;
	// 		token_treated += dll_size_between(start, end);
	// 		print_cmd_borned(start, end);
	// 	}
	// 	end = end->next;
	// }
	return (true);
	(void)config;
	(void)ast;
}
