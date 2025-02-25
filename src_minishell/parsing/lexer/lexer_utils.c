/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:59:51 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/13 20:59:49 by maecarva         ###   ########.fr       */
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
		printf("token: str = [%s], type = [", ptr_to_lexertoklist(tmp->content)->token);
		switch (ptr_to_lexertoklist(tmp->content)->type) {
			case PIPE_TOKEN:
				printf("%s]\n", "PIPE_TOKEN");
				break ;
			case TRUNCATE:
				printf("%s]\n", "TRUNCATE");
				break ;
			case APPEND:
				printf("%s]\n", "APPEND");
				break ;
			case REDIRECT_INPUT:
				printf("%s]\n", "REDIRECT_INPUT");
				break ;
			case HEREDOC:
				printf("%s]\n", "HERE_DOC");
				break ;
			case CMD:
				printf("%s]\n", "CMD");
				break ;
			case ARGS:
				printf("%s]\n", "ARGS");
				break ;
			case FILE_ARG:
				printf("%s]\n", "FILE_ARG");
				break ;
			case AND:
				printf("%s]\n", "AND");
				break ;
			case OR:
				printf("%s]\n", "OR");
				break ;
			case PARENTHESIS_L:
				printf("%s]\n", "PARENTHESIS_L");
				break ;
			case PARENTHESIS_R:
				printf("%s]\n", "PARENTHESIS_R");
				break ;
			default:
				printf("%s]\n", "ERROR");
				break ;
		}
		tmp = tmp->next;
		if (tmp == list)
			break ;
	}
}

t_lexertoklist	*ptr_to_lexertoklist(void *token)
{
	return ((t_lexertoklist *)token);
}

void	free_token_list(t_dlist **dlist)
{
	t_dlist	*tmp;
	int		size;

	size = dll_size(dlist);
	if (!(*dlist))
		return ;
	tmp = *dlist;
	while (size > 0)
	{
		tmp = tmp->next;
		
		free(ptr_to_lexertoklist((*dlist)->content)->token);
		free((*dlist)->content);
		free(*dlist);
		*dlist = tmp;
		size--;
	}
	*dlist = NULL;
}
