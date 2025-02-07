/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 12:18:01 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/07 16:21:38 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	print_token_list(t_dlist **dlist)
{
	t_dlist	*list;
	t_dlist	*tmp;

	if (!(*dlist))
		return ;
	list = *dlist;
	tmp = list;
	while (tmp)
	{
		printf("token: str = [%s] type = [", ptr_to_lexertoklist(tmp->content)->token);
		switch (ptr_to_lexertoklist(tmp->content)->type) {
			case PIPE_TOKEN:
				p("%s]\n", "PIPE_TOKEN");
				break ;
			case TRUNCATE:
				p("%s]\n", "TRUNCATE");
				break ;
			case APPEND:
				p("%s]\n", "APPEND");
				break ;
			case REDIRECT_INPUT:
				p("%s]\n", "REDIRECT_INPUT");
				break ;
			case HEREDOC:
				p("%s]\n", "HERE_DOC");
				break ;
			case CMD:
				p("%s]\n", "CMD");
				break ;
			case ARGS:
				p("%s]\n", "ARGS");
				break ;
			case FILE_ARG:
				p("%s]\n", "FILE_ARG");
				break ;
			default:
				p("%s]\n", "ERROR");
				break ;
		}
		tmp = tmp->next;
		if (tmp == list)
			break ;
	}
}

bool	lexer(char *cmd)
{
	t_dlist	*splited;

	splited = NULL;
	if (!cmd)
		return (true);
	splited = spliter(cmd);
	print_token_list(&splited);
	if (!splited)
		return (false);
	return (true);
}
