/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:25:54 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/18 16:19:58 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

// <Makefile cat| echo "$PWD 'hola'" ~/src | 'tr' -d / >outfile

void	delete_doubles_quotes_end_str(char *cmd)
{
	if (!cmd)
		return ;
	if ((cmd[ft_strlen(cmd) - 1] == '\'' && cmd[ft_strlen(cmd) - 2] == '\'')
		|| (cmd[ft_strlen(cmd) - 1] == '\"' && cmd[ft_strlen(cmd) - 2] == '\"'))
	{
		ft_bzero(&cmd[ft_strlen(cmd) - 2], 2);
	}
}

t_btree	*parse_cmd2(char *cmd, t_config *config)
{
	t_btree	*ast;
	char	*trimmed;
	t_dlist	*lexed;

	if (!cmd)
		return (NULL);
	ast = NULL;
	trimmed = NULL;
	// 1 : trim cmd
	trimmed = ft_strtrim(cmd, WHITESPACES);
	if (!trimmed)
		return (NULL);
	if (ft_strlen(trimmed) == 0)
		return (free(trimmed), NULL);

	// 2 : check invalid quotes + redir/pipes at end of string
	if (check_invalid_input(trimmed))
	{
		config->last_error_code = 2;
		return (free(trimmed), NULL);
	}
	// delete empty quotes
	delete_doubles_quotes_end_str(trimmed);

	// 3 : lexer string and check invalid redirections
	if (!lexer(trimmed, &lexed))
	{
		config->last_error_code = 2;
		return (free(trimmed), NULL);
	}
	// 4 : expand $
	if (!expander(lexed, config))
	{
		config->last_error_code = 2;
		return (free(trimmed), free_token_list(&lexed), NULL);
	}

	// print_token_list(&lexed);
	// create ast
	if (!create_ast(&ast, lexed, config))
	{
		printf("failed to create ast\n");
		config->last_error_code = 2;
		return (free(trimmed), free_token_list(&lexed), NULL);
	}
	// print_arbre(ast, 0);
	free_token_list(&lexed);
	free(trimmed);
	return (ast);
}
