/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.back.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 16:50:40 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/14 17:17:02 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

// free all allocated memory and clean function
bool	expand_token(char	**tokenstr, char **envp, t_config *config)
{
	char	*ptrs[4]; // 0 = varname, 1 = var value, 2 = expanded, 3 = rest
	int		i;
	char	*s;
	int		sub[2]; // 0 = start, 1 = len
	char	*lasterrorcode;

	lasterrorcode = ft_itoa(config->last_error_code);
	if (!(*tokenstr))
		return (false);
	s = *tokenstr;
	i = 0;
	while (s[i])
	{
		ft_bzero(ptrs, sizeof(char *) * 4);
		ft_bzero(sub, sizeof(int) * 2);
		if (s[i] == '$' && s[i + 1] != '\0' && !ft_isspace(s[i + 1]) && ft_is_in_charset(s[i + 1], "\'\""))
			ft_strlcpy(&s[i], &s[i + 1], ft_strlen(&s[i]));
		if (s[i] == '$' && s[i + 1] != '\0' && !ft_isspace(s[i + 1]) && !ft_is_in_charset(s[i + 1], EXPAND_CHARSET))
		{
			i++;
			if (s[i] == '\0')
			{
				s[i - 1] = '\0';
				return (true);
			}
			// classic var
			sub[0] = i;
			while (s[i + sub[1]] && ft_isalnum(s[i + sub[1]]))
				sub[1] += 1;
			ptrs[0] = ft_substr(s, sub[0], sub[1]);
			ptrs[1] = get_value_by_name(envp, ptrs[0]);
			if (ptrs[1] == NULL) // invalid varname
			{
				free(ptrs[0]);
				if (s[i + sub[1]] == '\0')
				{
					while (s[i + sub[1]] != '$')
					{
						s[i + sub[1]] = '\0';
						sub[1] -= 1;
					}
					s[i + sub[1]] = '\0';
				}
				else
				{
					char *start = &s[i - 1];
					char *end = &s[i + sub[1]];
					int	lentomove = ft_strlen(&s[i + sub[1]]) + 1;
					ft_memmove(start, end, lentomove);
				}
				continue ;
			}
			ft_free_simple_ptr(&ptrs[0]);
			ptrs[0] = ft_substr(s, 0, i - 1);
			ptrs[3] = ft_substr(s, sub[1] + i, ft_strlen(s) - sub[1]);
			ptrs[2] = ft_str_three_join(ptrs[0], ptrs[1], ptrs[3]);
			i += ft_strlen(ptrs[1]) - 1;
			free(ptrs[0]);
			free(ptrs[1]);
			free(ptrs[3]);
			s = ptrs[2];
			continue ;
		}
		if (ft_strnstr(&s[i], "$$", ft_strlen("$$")) == &s[i])
		{
			// expand pid
			ptrs[0] = ft_substr(s, 0, i);
			ptrs[3] = ft_substr(s, 2 + i, ft_strlen(s) - i + 2);
			ptrs[2] = ft_str_three_join(ptrs[0], config->pidstr, ptrs[3]);
			free(ptrs[0]);
			free(ptrs[1]);
			free(ptrs[3]);
			s = ptrs[2];
			i += ft_strlen(config->pidstr);
			continue ;
		}
		if (ft_strnstr(&s[i], "$?", ft_strlen("$?")) == &s[i])
		{
			ptrs[0] = ft_substr(s, 0, i);
			ptrs[3] = ft_substr(s, 2 + i, ft_strlen(s) - i + 2);
			ptrs[2] = ft_str_three_join(ptrs[0], lasterrorcode, ptrs[3]);
			free(ptrs[0]);
			free(ptrs[1]);
			free(ptrs[3]);
			s = ptrs[2];
			i += ft_strlen(lasterrorcode);
		}
		i++;
	}
	*tokenstr = s;
	return (true);
}

// bool	check_expansion(char *token)
// {
// 	bool	squote;
// 	bool	dquotes;
// 	int		numexp;
// 	int		i;
//
// 	if (!token)
// 		return (false);
// 	squote = false;
// 	dquotes = false;
// 	i = 0;
// 	numexp = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '\'')
// 			squote = !squote;
// 		if (token[i] == '\"')
// 			dquotes = !dquotes;
// 		if (token[i] == '$' && token[i + 1] != '$' && (dquotes == true || squote == false))
// 			numexp++;
// 		i++;
// 	}
// 	if (numexp == 0)
// 		return (false);
// 	return (true);
// }
bool	check_expansion(char *token)
{
	bool	squote;
	bool	dquotes;
	int		dqbefore;
	int		sqbefore;
	int		numexp;
	int		i;

	if (!token)
		return (false);
	squote = false;
	dquotes = false;
	i = 0;
	numexp = 0;
	if (ft_count_char_in_str(token, '\"') == 0 && ft_count_char_in_str(token, '\'') == 0 && ft_is_in_charset('$', token))
		return (true);
	while (token[i])
	{
		sqbefore = 0;
		dqbefore = 0;
		if (token[i] == '\'')
			squote = !squote;
		if (token[i] == '\"')
			dquotes = !dquotes;
		if (token[i] == '$' && token[i + 1] != '$')
		{
			if (dquotes == false && squote == false && (ft_first_char_in_charset(token, "\'\"") == '\"' || ft_first_char_in_charset(token, "\'\"") == '\0')
				&& ft_first_char_in_charset_rev(token, "\'\"", i) != '\'')
				numexp++;
			else if (ft_first_char_in_charset(token, "\"") == '\"' && ft_first_char_in_charset_rev(token, "\'\"", i) == '\'' && ft_count_char_in_str_rev(token, '\"', i) % 2 != 0)
				numexp++;
			else if (squote == false && ft_first_char_in_charset_rev(token, "\'\"", i) != '\'')
				numexp++;
			else if (squote == false && ft_count_char_in_str_rev(token, '\"', i) == 0)
				numexp++;
		}
		i++;
	}
	if (numexp == 0)
		return (false);
	return (true);
}


void	clean_quotes(char *s)
{
	int		i;
	int		j;
	bool	quoted;

	if (!s)
		return ;
	i = 0;
	quoted = false;
	while (s[i])
	{
		j = 0;
		if (s[i] == '\'' && quoted == false)
		{
			j = i + 1;
			while (s[j] && s[j] != '\'')
				j++;
			if (s[j] == '\0')
				break ;
			ft_strlcpy(&s[j], &s[j + 1], ft_strlen(&s[j]));
			ft_strlcpy(&s[i], &s[i + 1], ft_strlen(&s[i]));
			i = j - 2;
		}
		else if (s[i] == '\"' && quoted == false)
		{
			j = i + 1;
			while (s[j] && s[j] != '\"')
				j++;
			if (s[j] == '\0')
				break ;
			ft_strlcpy(&s[j], &s[j + 1], ft_strlen(&s[j]));
			ft_strlcpy(&s[i], &s[i + 1], ft_strlen(&s[i]));
			i = j - 2;
		}
		i++;
	}
}

bool	expander(t_dlist *lexed_list, t_config *config)
{
	t_dlist	*tmp;
	t_dlist	*tmp2;

	if (!lexed_list)
		return (false);
	tmp = lexed_list;
	while (tmp)
	{
		if (ft_strchr(ptr_to_lexertoklist(tmp->content)->token, '$'))
		{
			if (check_expansion(ptr_to_lexertoklist(tmp->content)->token))
			{
				expand_token(&ptr_to_lexertoklist(tmp->content)->token, config->environnement, config);
				if (ft_strlen(ptr_to_lexertoklist(tmp->content)->token) == 0 && dll_size(&lexed_list) > 1)
				{
					tmp2 = tmp;
					tmp->prev->next = tmp->next;
					tmp2->next->prev = tmp2->prev;
				}
			}
		}
		expand_wildcards(&ptr_to_lexertoklist(tmp->content)->token);
		clean_quotes(ptr_to_lexertoklist(tmp->content)->token);
		tmp = tmp->next;
		if (tmp == lexed_list)
			break ;
	}
	return (true);
}
