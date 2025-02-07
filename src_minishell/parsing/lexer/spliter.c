/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:01:37 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/07 17:16:18 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	putstrn(char *str, int start, int end)
{
		write(1, &str[start], end);
		ft_putchar_fd('\n', 1);
		start++;
}

bool	is_in_same_command(t_dlist **dlist)
{
	t_dlist	*current_node;

	current_node = (*dlist)->prev;
	if (current_node == (*dlist))
		return (false);
	while (1)
	{
		if (ptr_to_lexertoklist(current_node->content)->type == PIPE_TOKEN)
			return (false);
		if (ptr_to_lexertoklist(current_node->content)->type == CMD)
			return (true);
		if (current_node == *dlist)
			break ;
		current_node = current_node->prev;
	}
	return (false);
}

t_lexertok	get_token_type(char *token, t_dlist **dlist)
{
	t_lexertoklist	*tmp;
	t_lexertok		type;

	type = ERROR;
	tmp = NULL;

	if (token[0] == '|')
		type = PIPE_TOKEN;
	else if (token[0] == '<' && token[1] == '\0')
		type = REDIRECT_INPUT;
	else if (token[0] == '>' && token[1] == '\0')
		type = TRUNCATE;
	else if (token[0] == '>' && token[1] == '>')
		type = APPEND;
	else if (token[0] == '<' && token[1] == '<')
		type = HEREDOC;
	else
	{
		if ((*dlist) && (*dlist)->prev)
		{
			tmp = ptr_to_lexertoklist((*dlist)->prev->content);
			if (tmp->type == CMD)
				type = ARGS;
			else if ((tmp->type >= TRUNCATE && tmp->type <= HEREDOC))
				type = FILE_ARG;
			else if (tmp->type >= ARGS && tmp->type <= FILE_ARG && is_in_same_command(dlist))
				type = ARGS;
			else 
				type = CMD;
		}
		else 
			type = CMD;
	}
	return (type);
}

bool	add_to_token_list(t_dlist **dlist, char *cmd, int start, int end)
{
	t_dlist			*new;
	t_lexertoklist	*token;

	new = NULL;
	token = ft_calloc(sizeof(t_lexertoklist), 1);
	if (!token)
		return (false);
	token->token = ft_calloc(sizeof(char), end + 1);
	if (!token->token)
		return (free(token), false);
	ft_strlcpy(token->token, &cmd[start], end + 1);
	token->type = get_token_type(token->token, dlist);
	new = dll_new(token);
	if (!new)
		return (free(token->token), free(token), false);
	*dlist = dll_add_back(dlist, new);
	return (true);
}

// todo
// allocate list and put each element inside
// assign a token to each element
// print list + token

t_dlist	*spliter(char *cmd)
{
	t_dlist	*splited;
	int		start;
	int		end;
	int		i;

	if (!cmd)
		return (NULL);
	splited = NULL;
	start = 0;
	end = 0;
	i = 0;
	while (cmd[i] != '\0')
	{
		if (ft_strchr(SPECIALS_TOKEN, cmd[i]))
		{
			start = i;
			if (cmd[i] == cmd[i + 1])
			{
				end = 2;
				putstrn(cmd, start, end);
				add_to_token_list(&splited, cmd, start, end);
				i += 2;
			}
			else 
			{
				end = 1;
				putstrn(cmd, start, end);
				add_to_token_list(&splited, cmd, start, end);
				i += 1;
			}
		}
		else if (cmd[i] == '"')
		{
			start = i;
			end = start + 1;
			while (cmd[end] != '"')
				end++;
			end ++;
			putstrn(cmd, start, end - start);
			add_to_token_list(&splited, cmd, start, end);
			i += end - i;
		}
		else {
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			start = i;
			while (cmd[i] && !ft_isspace(cmd[i]) && !ft_strchr(SPECIALS_TOKEN, cmd[i]))
				i++;
			end = i - start;
			putstrn(cmd, start, end);
			add_to_token_list(&splited, cmd, start, end);
		}
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
	}
	return (splited);
}
