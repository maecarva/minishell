/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 11:25:54 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 13:31:56 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

t_btree	*error_parsing(char *message, t_parser **parser, int code)
{
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	if (!parser || !*parser)
		return (NULL);
	(*parser)->config->last_error_code = code;
	if ((*parser)->lexed)
		free_token_list(&(*parser)->lexed);
	if ((*parser)->trimmed)
		ft_free_simple_ptr(&(*parser)->trimmed);
	free(*parser);
	return (NULL);
}

t_parser	*init_parser(t_config *config)
{
	t_parser	*parser;

	if (!config)
		return (NULL);
	parser = ft_calloc(1, sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->trimmed = NULL;
	parser->lexed = NULL;
	parser->ast = NULL;
	parser->config = config;
	return (parser);
}

t_btree	*clean_parser(t_parser *parser)
{
	t_btree	*ast;

	if (!parser)
		return (NULL);
	ast = parser->ast;
	ft_free_simple_ptr(&parser->trimmed);
	free_token_list(&parser->lexed);
	free(parser);
	return (ast);
}

t_btree	*parse_cmd(char *cmd, t_config *config)
{
	t_parser	*parser;

	if (!cmd)
		return (NULL);
	parser = init_parser(config);
	if (!parser)
		return (error_parsing("Failed to initialize parser.", &parser, 2));
	parser->trimmed = ft_strtrim(cmd, WHITESPACES);
	if (!parser->trimmed)
		return (NULL);
	if (ft_strlen(parser->trimmed) == 0)
		return (error_parsing(NULL, &parser, 2));
	if (check_invalid_input(parser->trimmed, config))
		return (error_parsing(NULL, &parser, 2));
	if (ft_strchr(parser->trimmed, '$'))
		expand_token(&(parser->trimmed), config->environnement, config, false);
	if (ft_strlen(parser->trimmed) == 0)
		return (error_parsing(NULL, &parser, 0));
	if (!lexer(parser->trimmed, &parser->lexed))
		return (error_parsing(NULL, &parser, 2));
	if (!expander(&parser->lexed, config))
		return (error_parsing(NULL, &parser, 2));
	if (!create_ast(&parser->ast, parser->lexed, config))
		return (error_parsing("Failed to create AST.", &parser, 2));
	return (clean_parser(parser));
}
