/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_constructor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:49:24 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 16:35:14 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

bool	cmd_is_empty(char **cmd_split, int size)
{
	int	i;

	i = 0;
	while (i <= size)
	{
		if (cmd_split[i] != NULL)
			return (false);
		i++;
	}
	return (true);
}

bool	cmd_contains_pipe(char **cmd_split, int *index)
{
	int	i;

	i = 0;
	while (cmd_split[i] != NULL)
	{
		if (cmd_split[i][0] == PIPECHAR)
		{
			*index = i;
			return (true);
		}
		i++;
	}
	return (false);
}

void	construct_ast(t_btree **ast, char **cmd_split, int cmd_len)
{
	int	i;

	i = 0;
	if (cmd_is_empty(cmd_split, cmd_len) || !ast)
		return ;
	if (cmd_contains_pipe(cmd_split, &i))
	{
		*ast = create_special_node(PIPE);
		free(cmd_split[i]);
		cmd_split[i] = NULL;
		construct_ast(&(*ast)->left, cmd_split, cmd_len - i);
		construct_ast(&(*ast)->right, &cmd_split[i + 1], cmd_len);
	}
	else {
		*ast = create_command_node(cmd_split);
		free(cmd_split[i]);
		cmd_split[i] = NULL;
	}
}
