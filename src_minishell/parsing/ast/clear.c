/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:31:00 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/09 19:34:23 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	free_ast(t_btree **ast)
{
	t_node2	*n;

	if (!(*ast))
		return ;
	free_ast(&(*ast)->left);
	free_ast(&(*ast)->right);

	n = (t_node2 *)(*ast)->item;
	if (n->file)
		free(n->file);
	if (n->command)
		free(n->command);
	free(n);
	free(*ast);
	*ast = NULL;
}
