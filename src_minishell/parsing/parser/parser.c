/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:25:54 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/09 15:41:12 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

// <Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile

t_btree	*parse_cmd2(char *cmd, t_config *config)
{
	t_btree	*ast;
	char	*trimmed;
	t_dlist	*lexed;

	if (!cmd)
		return (NULL);
	ast = NULL;
	trimmed = NULL;
	// printf("command to parse : {%s}\n", cmd);
	// 1 : trim cmd
	trimmed = ft_strtrim(cmd, WHITESPACES);
	if (!trimmed)
		return (NULL);
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed), NULL);

	// 2 : check invalid quotes + redir/pipes at end of string
	if (check_invalid_input(trimmed))
		return (free(trimmed), NULL);
	// 3 : lexer string and check invalid redirections
	if (!lexer(trimmed, &lexed))
		return (free(trimmed), NULL);
	// 4 : expand $
	if (!expander(lexed, config))
		return (free_token_list(&lexed), NULL);

	// print_token_list(&lexed);
	// create ast
	if (!create_ast(&ast, lexed, config))
		printf("failed to create ast\n");
	// print_arbre(ast, 0);
	free_token_list(&lexed);
	free(trimmed);
	return (ast);
}
