/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 17:14:38 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/27 15:24:47 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

// 0: varname, 1: value, 2: beforevar, 3: aftervar
int	expand_pls(char **str, t_config *config,
			int *index, bool expand_specials)
{
	int		j;
	char	*s;

	if (!str || !index)
		return (0);
	s = *str;
	if (s[*index + 1] == '\0')
		return (0);
	j = *index + 1;
	if (ft_isdigit(s[j]))
		return ((void)ft_memmove(&s[*index],
				&s[j + 1], ft_strlen(&s[j]) + 1), 0);
	else if (s[j] == '\"' || s[j] == '\'')
		return ((void)ft_memmove(&s[*index], &s[j], ft_strlen(&s[j]) + 1), 0);
	else if (s[j] == '?')
		return (expand_last_error(str, config, index));
	else if (s[j] == '$')
		return (expand_pid(str, config, index));
	else if (s[j] == '/' || s[j] == '=')
	{
		*index += j;
		return (1);
	}
	return (expand_classic(str, config, index, expand_specials));
}

// 0: no quotes, 1: ', 2: "
void	expand_token(char **tokenstr, char **envp,
				t_config *config, bool expand_specials)
{
	int		i;
	int		state;
	bool	expand;

	if (!tokenstr || !*tokenstr || !envp || !config)
		return ;
	state = 0;
	expand = false;
	i = -1;
	while ((*tokenstr)[++i])
	{
		expander_quote_brain(*tokenstr, &i, &state, &expand);
		if (expand)
		{
			expand = false;
			if ((*tokenstr)[i + 1] == '\"' && state == 2)
				continue ;
			if (expand_pls(tokenstr, config, &i, expand_specials) == 0)
				i = -1;
			state = 0;
			continue ;
		}
	}
}

bool	manage_files(t_dlist **tmp, t_dlist **lexed_list)
{
	t_dlist	*newlist;
	char	**files;
	bool	breakloop;

	newlist = NULL;
	breakloop = false;
	files = expand_wildcards(&ptr_to_lexertoklist((*tmp)->content)->token);
	if (files != NULL)
	{
		newlist = create_arg_list(files, *tmp);
		ft_free_double_ptr(&files);
		if (dll_size(lexed_list) == 1)
		{
			dll_clear(lexed_list);
			*lexed_list = newlist;
			return (true);
		}
		suppress_element(tmp);
		if (dll_size(lexed_list) == 1)
			breakloop = true;
		dll_insert(*tmp, newlist);
	}
	return (breakloop);
}

bool	expander(t_dlist **lexed_list, t_config *config)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (!*lexed_list)
		return (false);
	tmp = *lexed_list;
	while (tmp)
	{
		if (ft_strchr(ptr_to_lexertoklist(tmp->content)->token, '$')
			&& ptr_to_lexertoklist(tmp->prev->content)->type != HEREDOC)
		{
			expand_token(&ptr_to_lexertoklist(tmp->content)->token,
				config->environnement, config, true);
			if (ft_strlen(ptr_to_lexertoklist(tmp->content)->token) == 0
				&& dll_size(lexed_list) > 1)
				delete_token_invalid_var(&tmp, &tmp2);
		}
		expand_tilde(&ptr_to_lexertoklist(tmp->content)->token, config);
		if (manage_files(&tmp, lexed_list))
			break ;
		tmp = tmp->next;
		if (tmp == *lexed_list)
			break ;
	}
	return (true);
}
