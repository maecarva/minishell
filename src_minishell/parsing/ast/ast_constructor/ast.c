/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 14:35:38 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 22:29:16 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

void	construct(t_btree **ast, t_dlist *start, t_dlist *end, bool split3)
{
	t_dlist	*tmp;

	if (!ast || start == NULL || end == NULL)
		return ;
	tmp = NULL;
	if (list_contain_parenthesis(start, end)
		&& list_contain_operator(start, end))
		handle_parenthesis_ast(ast, start, end, split3);
	else if (list_contain_operator(start, end))
		handle_and_or_ast(ast, start, end, split3);
	else if (list_contain_pipe(start, end, &tmp))
	{
		*ast = create_operator_node(ptr_to_lexertoklist(tmp->content)->type);
		if (!*ast)
			return ;
		construct(&(*ast)->left, start, tmp->prev, false);
		construct(&(*ast)->right, tmp->next, end, false);
	}
	else
		*ast = create_cmd_node(start, end);
}

void	assing_type(t_node2 *n)
{
	if ((ft_strnstr(n->command[0], "echo", ft_strlen("echo")) == n->command[0])
		&& (n->command[0][4] == '\0'))
		n->type = ECHO;
	else if (ft_strnstr(n->command[0], "cd", ft_strlen("cd")) == n->command[0])
		n->type = CD;
	else if ((ft_strnstr(n->command[0], "pwd", ft_strlen("pwd"))
			== n->command[0]) && (n->command[0][3] == '\0'))
		n->type = PWD;
	else if (ft_strnstr(n->command[0], "export", ft_strlen("export"))
		== n->command[0])
		n->type = EXPORT;
	else if (ft_strnstr(n->command[0], "unset", ft_strlen("unset"))
		== n->command[0])
		n->type = UNSET;
	else if (ft_strnstr(n->command[0], "env", ft_strlen("env"))
		== n->command[0])
		n->type = ENV;
	else if (ft_strnstr(n->command[0], "exit", ft_strlen("exit"))
		== n->command[0])
		n->type = EXIT;
}

void	finalise_ast(t_btree **ast, t_config *config)
{
	t_node2	*n;

	if (!(*ast))
		return ;
	n = (t_node2 *)((*ast)->item);
	if (n->type == CMD && n->command[0] != NULL)
		assing_type(n);
	finalise_ast(&(*ast)->left, config);
	finalise_ast(&(*ast)->right, config);
}

bool	create_ast(t_btree **ast, t_dlist *tokenlist, t_config *config)
{
	if (!tokenlist || !config)
		return (false);
	construct(ast, tokenlist, tokenlist->prev, false);
	finalise_ast(ast, config);
	return (true);
}
