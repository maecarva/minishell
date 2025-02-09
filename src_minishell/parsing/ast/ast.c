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

void	construct(t_btree **ast, t_dlist *start, t_dlist *end) // < infile1 cat -e << here_doc > outfile.txt >> appendfile.txt > outfile2 | echo
{
	t_dlist	*tmp;

	if (start == NULL || end == NULL)
		return ;
	tmp = NULL;
	if (list_contain_pipe(start, end, &tmp))
	{
		// create pipe node
		*ast = create_pipe_node();
		if (!ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev);
		construct(&(*ast)->right, tmp->next, end);
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
	construct(ast, tokenlist, tokenlist->prev);
	print_arbre(*ast, 0);
	if (!tokenlist || !config)
		return (false);
	return (true);
}
