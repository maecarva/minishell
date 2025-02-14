/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_in_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 18:11:12 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/14 19:56:31 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	move_in_ast(t_config **ms_data)
// {
// 	t_lexertok	type;
// 	t_btree	*original_ast;

// 	original_ast = (*ms_data)->ast;
// 	type = ((t_node2 *)((*ms_data)->ast->item))->type;
// 	if (type == OR || type == AND)
// 	{
// 		(*ms_data)->ast = (*ms_data)->ast->left;
// 		//print_arbre(ms_data->ast, 0);
// 		check_type_execute(*ms_data);
// 		if (type == OR && (*ms_data)->last_error_code != 0)
// 		{
// 			(*ms_data)->ast = original_ast;
// 			(*ms_data)->ast = (*ms_data)->ast->right;
// 			check_type_execute(*ms_data);
// 		}
// 		else if (type == AND && (*ms_data)->last_error_code == 0)
// 		{
// 			(*ms_data)->ast = original_ast;
// 			(*ms_data)->ast = (*ms_data)->ast->right;
// 			check_type_execute(*ms_data);
// 		}
// 	}
// }

void	execute_ast(t_btree *actual_ast, t_config **ms_data)
{
	t_lexertok	type;

	if (!actual_ast)
		return ;
	type = ((t_node2 *)(actual_ast->item))->type;
	(*ms_data)->ast = actual_ast;
	if (type == PIPE_TOKEN || type == CMD)
	{
		printf("=====================\n");
		print_arbre(actual_ast, 0);
		printf("=====================\n");
		check_type_execute(*ms_data);
		return ;
	}
	execute_ast(actual_ast->left, ms_data);
	if ((type == OR && (*ms_data)->last_error_code != 0) || (type == AND && (*ms_data)->last_error_code == 0))
		execute_ast(actual_ast->right, ms_data);
}
