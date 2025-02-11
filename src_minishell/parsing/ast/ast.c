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

void	construct(t_btree **ast, t_dlist *start, t_dlist *end)
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

// separate list to ditinguish cmd && pipes
bool	create_ast(t_btree **ast, t_dlist *tokenlist, t_config *config)
{
	if (!tokenlist || !config)
		return (false);
	construct(ast, tokenlist, tokenlist->prev);
	handle_redirections(ast, tokenlist, tokenlist->prev);
	finalise_ast(ast);
	return (true);
}
