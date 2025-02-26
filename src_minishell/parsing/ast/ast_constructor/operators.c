/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 21:23:04 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 21:32:23 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

void	first_split(t_btree **ast, t_dlist *start, t_dlist *end, bool split3)
{
	t_dlist	*tmp;

	tmp = NULL;
	get_last_and_or(start, end, &tmp);
	*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
	if (!*ast)
		return ;
	construct(&(*ast)->left, start, tmp->prev, true);
	construct(&(*ast)->right, tmp->next, end, false);
	(void)split3;
}

void	second_split(t_btree **ast, t_dlist *start, t_dlist *end, bool split3)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	get_last_and_or(start, end, &tmp);
	if (!tmp)
		return ;
	get_last_and_or(start, tmp->prev, &tmp2);
	if (!tmp2)
		return ;
	*ast = create_operator_node(ptr_to_lexertoklist(tmp2->content)->type);
	construct(&(*ast)->left, start, tmp2->prev, true);
	construct(&(*ast)->right, tmp2->next, end, false);
	(void)split3;
}

void	handle_multiple_type_and_or(t_btree **ast, t_dlist *start,
								t_dlist *end, bool split3)
{
	if (split3 == false)
		first_split(ast, start, end, split3);
	else
		second_split(ast, start, end, split3);
}

void	handle_and_or_ast(t_btree **ast, t_dlist *start,
						t_dlist *end, bool split3)
{
	t_dlist	*tmp;

	tmp = NULL;
	if (multiple_and_or(start, end) == false)
	{
		get_first_and_or(start, end, &tmp);
		*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
		if (!ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev, false);
		construct(&(*ast)->right, tmp->next, end, false);
	}
	else
		handle_multiple_type_and_or(ast, start, end, split3);
}

void	handle_parenthesis_ast(t_btree **ast, t_dlist *start,
							t_dlist *end, bool split3)
{
	t_dlist	*tmp;

	tmp = NULL;
	get_first_valid_operator(&start, &end, &tmp);
	if (tmp != NULL)
	{
		*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
		if (!ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev, false);
		construct(&(*ast)->right, tmp->next, end, false);
	}
	else
	{
		get_last_and_or(start, end, &tmp);
		*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
		if (!*ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev, true);
		construct(&(*ast)->right, tmp->next, end, false);
	}
	(void)split3;
}
