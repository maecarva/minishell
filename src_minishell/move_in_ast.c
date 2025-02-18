/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_in_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:11:12 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/18 16:02:34 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_message(char *s1, char *s2, char *s3)
{
	if (s1)
		ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	if (s3)
		ft_putendl_fd(s3, 2);
}

void	execute_ast(t_btree *actual_ast, t_config *ms_data)
{
	t_lexertok	type;

	if (!actual_ast)
		return ;
	type = ((t_node2 *)(actual_ast->item))->type;
	ms_data->ast = actual_ast;
	if (type != OR && type != AND)
	{
		check_type_execute(ms_data);
		return ;
	}
	// print_arbre(actual_ast, 0);
	execute_ast(actual_ast->left, ms_data);
	if ((type == OR && ms_data->last_error_code != 0) || (type == AND && ms_data->last_error_code == 0))
		execute_ast(actual_ast->right, ms_data);
}
