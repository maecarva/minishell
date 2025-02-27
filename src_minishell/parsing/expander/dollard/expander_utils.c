/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:46:32 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 19:08:49 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

bool	is_quoted(bool *quotes)
{
	return (quotes[0] == true || quotes[1] == true);
}

bool	is_special_var(char *s)
{
	if (!s)
		return (false);
	if (ft_strlen(s) == 1)
	{
		if (ft_is_in_charset(s[0], "|<>"))
			return (true);
	}
	else if (ft_strlen(s) == 2)
	{
		if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
			return (true);
	}
	return (false);
}

void	free_array(char **a, int size, int dont_free_idx)
{
	int	i;

	if (!a)
		return ;
	i = 0;
	while (i < size)
	{
		if (a[i] != NULL && i != dont_free_idx)
			ft_free_simple_ptr(&a[i]);
		i++;
	}
}

void	expander_quote_brain(char *s, int *i, int *state, bool *expand)
{
	if (s[*i] == '<' && s[*i + 1] == '<')
	{
		while (s[*i] && s[*i] != '$')
			(*i)++;
		if (s[*i] == '$')
			(*i)++;
	}
	if (s[*i] == '\'' && *state == 0)
		*state = 1;
	else if (s[*i] == '\'' && *state == 1)
		*state = 0;
	else if (s[*i] == '\"' && *state == 0)
		*state = 2;
	else if (s[*i] == '\"' && *state == 2)
		*state = 0;
	else if (s[*i] == '$' && s[*i + 1] != '\0'
		&& (*state == 0 || *state == 2) && !ft_isspace(s[*i + 1]))
		*expand = true;
}
