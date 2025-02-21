/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 15:01:26 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/21 16:49:56 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

void	clean_quotes2(char *s)
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

void	clean_quotes_de_merde(char *s)
{
	char	lastquotescleaned;

	if (!s)
		return ;
	lastquotescleaned = -1;
	if (ft_strchr("\'\"", s[0]) && ft_strchr("\'\"", s[ft_strlen(s) - 1]) && s[0] == s[ft_strlen(s) - 1])
	{
		lastquotescleaned = s[0];
		s[ft_strlen(s)] = '\0';
		ft_strlcpy(s, &s[1], ft_strlen(&s[1]));
	
		while (s[0] == lastquotescleaned && s[ft_strlen(s) - 1] == lastquotescleaned && ft_strchr("\'\"", s[0]) && ft_strchr("\'\"", s[ft_strlen(s) - 1]) && s[0] == s[ft_strlen(s) - 1])
		{
			lastquotescleaned = s[0];
			s[ft_strlen(s)] = '\0';
			ft_strlcpy(s, &s[1], ft_strlen(&s[1]));
		}
	}
	else
		clean_quotes2(s);
}

char *remove_quotes(const char *s) {
    int i = 0, j = 0;
    int len = s ? ft_strlen(s) : 0;
    char *res = malloc(len + 1);
    if (!res)
       return NULL;
    int in_single_quote = 0;
    int in_double_quote = 0;
    
    while (s[i]) {
        if (s[i] == '\'' && !in_double_quote) {
            in_single_quote = !in_single_quote;
        }
        else if (s[i] == '\"' && !in_single_quote) {
            in_double_quote = !in_double_quote;
        }
        else {
            res[j++] = s[i];
        }
        i++;
    }
    res[j] = '\0';
    return res;
}


void	clean_quotes(char **s)
{
	char	*removed;


	removed = remove_quotes(*s);
	// printf("first: [%s]\n removed: [%s]\n", *s, removed);
	free(*s);
	*s = removed;
}
