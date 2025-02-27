/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:26 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/25 17:17:11 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	handle_wildcards(char *s, char *res, int *i, int *j)
{
	if (ft_is_in_charset(s[*i], "\'\"") && s[*i + 1] == '*'
		&& ft_is_in_charset(s[*i + 2], "\'\"") && s[*i] == s[*i + 2])
	{
		res[(*j)++] = s[*i];
		res[(*j)++] = s[(*i)++];
		res[(*j)++] = s[(*i)++];
	}
}

char	*remove_quotes(char *s)
{
	int		i;
	int		j;
	char	*res;
	int		in_single_quote;
	int		in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	i = -1;
	j = 0;
	res = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!res)
		return (NULL);
	while (s[++i])
	{
		handle_wildcards(s, res, &i, &j);
		if (s[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (s[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else
			res[j++] = s[i];
	}
	res[j] = '\0';
	return (res);
}

void	clean_quotes(char **s)
{
	char	*removed;

	if (!s || !*s)
		return ;
	removed = remove_quotes(*s);
	free(*s);
	*s = removed;
}
