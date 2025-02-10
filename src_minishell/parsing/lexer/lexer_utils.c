/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 15:59:51 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/08 17:28:04 by maecarva         ###   ########.fr       */
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
