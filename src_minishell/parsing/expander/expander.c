/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:14:38 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/23 19:13:33 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"
#include <readline/chardefs.h>

bool	is_quoted(bool *quotes)
{
	return (quotes[0] == true || quotes[1] == true);
}

void	expand_pls(char **str, char **env, t_config *config, int *index)
{
	char	*ptrs[4];// 0: varname, 1: value, 2: beforevar, 3: aftervar
	int		j;
	char	*s;

	if (!str || !index || !env)
		return ;
	ft_bzero(ptrs, sizeof(char *) * 4);
	s = *str;
	if (s[*index + 1] == '\0')
		return ;
	j = *index + 1;
	if (ft_isdigit(s[j]))
		return ((void)ft_memmove(&s[*index], &s[j + 1], ft_strlen(&s[j]) + 1));
	else if (s[j] == '\"' || s[j] == '\'')
		return ((void)ft_memmove(&s[*index], &s[j], ft_strlen(&s[j]) + 1));
	else if (s[j] == '?')
	{
		ptrs[1] = ft_itoa(config->last_error_code);
		ptrs[2] = ft_substr(s, 0, *index);
		ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
		ptrs[0] = ft_str_three_join(ptrs[2], ptrs[1], ptrs[3]);
		*index += ft_strlen(ptrs[1]) - 1;
		free(*str);
		free(ptrs[1]);
		free(ptrs[2]);
		free(ptrs[3]);
		*str = ptrs[0];
		return ;
	}
	else if (s[j] == '$')
	{
		ptrs[2] = ft_substr(s, 0, *index);
		ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
		ptrs[0] = ft_str_three_join(ptrs[2], config->pidstr, ptrs[3]);
		*index += ft_strlen(ptrs[1]) - 1;
		free(*str);
		free(ptrs[2]);
		free(ptrs[3]);
		*str = ptrs[0];
		return ;
	}
	while (s[j] && ((ft_isalnum(s[j]) || s[j] == '_') && (ft_isalnum(s[j + 1]) || s[j + 1] == '_')))
		j++;
	ptrs[0] = ft_substr(s, *index + 1 , j - *index);
	if (!ptrs[0])
		return ;
	ptrs[1] = get_value_by_name(env, ptrs[0]);
	free(ptrs[0]);
	if (!ptrs[1]) // no valid name
		ft_memmove(&s[*index], &s[j + 1], ft_strlen(&s[j]) + 1);
	else
	{
		ptrs[2] = ft_substr(s, 0, *index);
		ptrs[3] = ft_substr(s, j + 1, ft_strlen(s));
		ptrs[0] = ft_str_three_join(ptrs[2], ptrs[1], ptrs[3]);
		*index += ft_strlen(ptrs[1]) - 1;
		free(*str);
		free(ptrs[1]);
		free(ptrs[2]);
		free(ptrs[3]);
		*str = ptrs[0];
	}
}

void expand_token(char **tokenstr, char **envp, t_config *config)
{
	int		i;
	int		state; // 0: no quotes, 1: ', 2: "
	bool	expand;
	char	*s;

	if (!tokenstr || !*tokenstr || !envp || !config)
		return;

	s = *tokenstr;
	state = 0;
	expand = false;
	i = 0;
	while (s[i])
	{
		if (s[i] == '<' && s[i + 1] == '<')
		{
			while (s[i] && s[i] != '$')
				i++;
			if (s[i] == '$')
				i++;
		}
		if (s[i] == '\'' && state == 0)
			state = 1;
		else if (s[i] == '\'' && state == 1)
			state = 0;
		else if (s[i] == '\"' && state == 0)
			state = 2;
		else if (s[i] == '\"' && state == 2)
			state = 0;
		else if (s[i] == '$' && s[i + 1] != '\0' && (state == 0 || state == 2) && !ft_isspace(s[i + 1]))
			expand = true;
		if (expand)
		{
			if (s[i + 1] == '\"' && state == 2)
			{
				i++;
				expand = false;
				continue ;
			}
			expand_pls(tokenstr, envp, config, &i);
			expand = false;
			s = *tokenstr;
			i = 0;
			state = 0;
			continue ;
		}
		i++;
	}
}

t_dlist	*create_arg_list(char	**files, t_dlist *before)
{
	t_dlist	*lst;
	int		i;
	t_lexertoklist	*tmp;

	if (!files || !*files || !before)
		return (NULL);
	i = 0;
	lst = NULL;
	tmp = NULL;
	while (files[i])
	{
		tmp = ft_calloc(sizeof(t_lexertoklist), 1);
		if (!tmp)
			return (dll_clear(&lst), NULL);
		tmp->token = ft_strdup(files[i]);
		if (i == 0)
			tmp->type = ptr_to_lexertoklist(before->content)->type;
		else
			tmp->type = ARGS;
		dll_add_back(&lst, dll_new(tmp));
		tmp = NULL;
		i++;
	}
	return (lst);
}

void	suppress_element(t_dlist **lst)
{
	t_dlist	*before;
	t_dlist	*after;
	t_dlist	*tmp;

	if (!lst || !*lst)
		return ;
	if (dll_size(lst) == 1)
		free_token_list(lst);
	else if (dll_size(lst) == 2)
	{
		before = (*lst)->prev;
		tmp = (*lst);
		tmp->next = tmp;
		tmp->prev = tmp;
		before->prev = before;
		before->next = before;
		free_token_list(&tmp);
		*lst = before;
	}
	else
	{
		before = (*lst)->prev;
		after = (*lst)->next;
		tmp = (*lst);
		tmp->next = tmp;
		tmp->prev = tmp;
		before->next = after;
		after->prev = before;
		*lst = after;
		free_token_list(&tmp);
	}
}

bool	expander(t_dlist **lexed_list, t_config *config)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;
	t_dlist	*newlist;
	char	**files;
	bool	breakloop;

	if (!*lexed_list)
		return (false);
	tmp = *lexed_list;
	breakloop = false;
	while (tmp)
	{
		files = NULL;
		if (ft_strchr(ptr_to_lexertoklist(tmp->content)->token, '$') && ptr_to_lexertoklist(tmp->prev->content)->type != HEREDOC)
		{
			if (ft_strlen(ptr_to_lexertoklist(tmp->content)->token) == 0 && dll_size(lexed_list) > 1)
			{
				tmp2 = tmp;
				tmp->prev->next = tmp->next;
				tmp2->next->prev = tmp2->prev;
			}
		}
		files = expand_wildcards(&ptr_to_lexertoklist(tmp->content)->token);
		if (files != NULL)
		{
			// connect new args to existing cmd
			newlist = create_arg_list(files, tmp);
			ft_free_double_ptr(&files);
			// retire *
			if (dll_size(lexed_list) == 1)
			{
				dll_clear(lexed_list);
				*lexed_list = newlist;
				break ;
			}
			suppress_element(&tmp);
			if (dll_size(lexed_list) == 1)
				breakloop = true;
			dll_insert(tmp, newlist);
			if (breakloop)
				break ;
		}
		tmp = tmp->next;
		if (tmp == *lexed_list)
			break ;
	}
	return (true);
	(void)config;
}
