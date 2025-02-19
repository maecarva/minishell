/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:01:37 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/13 21:20:15 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	putstrn(char *str, int start, int end)
{
	int	i;
	i = start - 1;
	while (++i < end || str[i] == '\0')
		write(1, &str[i], 1);
	ft_putchar_fd('\n', 1);
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

	if (token[0] == '|' && token[1] == '\0')
		type = PIPE_TOKEN;
	else if (token[0] == '|' && token[1] == '|')
			type = OR;
	else if (token[0] == '&' && token[1] == '&')
			type = AND;
	else if (token[0] == '<' && token[1] == '\0')
		type = REDIRECT_INPUT;
	else if (token[0] == '>' && token[1] == '\0')
		type = TRUNCATE;
	else if (token[0] == '>' && token[1] == '>')
		type = APPEND;
	else if (token[0] == '<' && token[1] == '<')
		type = HEREDOC;
	else if (token[0] == '(')
		type = PARENTHESIS_L;
	else if (token[0] == ')')
		type = PARENTHESIS_R;
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

// specificite pour quotes
void	extract_quoted(char *cmd, int *i, int *start, int *end)
{
	bool	squote;
	bool	dquotes;
	char	cquote;

	cquote = cmd[*i];
	squote = false;
	dquotes = false;
	if (cquote == '\"')
		dquotes = true;
	else if (cquote == '\'')
		squote = true;
	*start = *i;
	*end = *start + 1;
	while (cmd[*end])
	{
		if (cmd[*end] == '\'' && cquote == cmd[*end])
			squote = !squote;
		if (cmd[*end] == '\"' && cquote == cmd[*end])
			dquotes = !dquotes;
		if (squote == false && dquotes == false && ft_isspace(cmd[*end]))
			break ;
		if (cmd[*end] == cquote && squote == false && dquotes == false && !ft_isalnum(cmd[*end + 1])
			&& !ft_is_in_charset(cmd[*end], "\'\""))
			break ;
		if (cmd[*end + 1] == '\0')
			break ;
		*end += 1;
	}
	*end += 1;
	*i = *end;
}

t_dlist	*spliter2(char *cmd)
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
				add_to_token_list(&splited, cmd, start, end);
				i += 2;
			}
			else 
			{
				end = 1;
				add_to_token_list(&splited, cmd, start, end);
				i += 1;
			}
		}
		else if (cmd[i] == '\"' || cmd[i] == '\'')
		{
			start = 0;
			end = 0;
			extract_quoted(cmd, &i, &start, &end);
			add_to_token_list(&splited, cmd, start, end - start);
		}
		else {
			while (cmd[i] && ft_isspace(cmd[i]))
				i++;
			start = i;
			while (cmd[i] && !ft_isspace(cmd[i]) && !ft_strchr(SPECIALS_TOKEN, cmd[i]))/* && !ft_is_in_charset(cmd[i], "\'\"")*/ // add quoted condition ?
				i++;
			end = i - start;
			add_to_token_list(&splited, cmd, start, end);
		}
		while (cmd[i] && ft_isspace(cmd[i]))
			i++;
	}
	return (splited);
}

t_dlist	*spliter(char *cmd)
{
	t_dlist	*splited;
	int		start;
	int		end;
	int		i;
	char	cquote;

	if (!cmd)
		return (NULL);
	splited = NULL;
	i = 0;
	cquote = 0;
	while (cmd[i] != '\0')
	{
		while (cmd[i] && ft_isspace(cmd[i])) // Ignorer les espaces au début
			i++;
		if (cmd[i] == '\0') // Si on atteint la fin de la commande, on arrête
			break;
		
		start = i;
		if (ft_strchr(SPECIALS_TOKEN, cmd[i])) // Cas des tokens spéciaux comme |, >, etc.
		{
			if (cmd[i] == cmd[i + 1]) // Si c'est un double token (>> ou <<)
			{
				end = i + 2;
				add_to_token_list(&splited, cmd, start, end - start);
				i += 2;
			}
			else 
			{
				end = i + 1;
				add_to_token_list(&splited, cmd, start, end - start);
				i += 1;
			}
		}
		else if (cmd[i] == '\"' || cmd[i] == '\'') // Cas des tokens entre guillemets
		{
			extract_quoted(cmd, &i, &start, &end);
			add_to_token_list(&splited, cmd, start, end - start);
		}
		else // Cas général : mot sans guillemets ni caractère spécial
		{
			while (cmd[i] && !ft_isspace(cmd[i]) && !ft_strchr(SPECIALS_TOKEN, cmd[i]))
			{
				if (cmd[i] == '\"' || cmd[i] == '\'') // Si on rencontre une quote
				{
					cquote = cmd[i];
					i++;
					while (cmd[i] && cmd[i] != cquote)
						i++;
				}
				else
					i++;
			}
			end = i;
			add_to_token_list(&splited, cmd, start, end - start);
		}
	}
	return (splited);
}
