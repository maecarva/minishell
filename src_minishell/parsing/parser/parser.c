/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:25:54 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/07 12:25:57 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

// <Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile

t_btree	*parse_cmd2(char *cmd)
{
	t_btree	*ast;
	char	*trimmed;

	if (!cmd)
		return (NULL);
	ast = NULL;
	trimmed = NULL;
	printf("command to parse : {%s}\n", cmd);
	// 1 : trim cmd
	trimmed = ft_strtrim(cmd, WHITESPACES);
	if (!trimmed)
		return (NULL);
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed), NULL);

	// 2 : check invalid quotes + redir/pipes at end of string
	if (check_invalid_input(trimmed))
		return (free(trimmed), NULL);
	// 3 : lexer
	if (!lexer(trimmed))
		return (free(trimmed), NULL);
	//	a : trim cmd by spaces and quotes



	return (ast);
}
