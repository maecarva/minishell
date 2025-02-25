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

char *remove_quotes(const char *s) {
	int		i;
	int		j;
	int		len;
	char	*res;
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	i = 0;
	j = 0;
	len = ft_strlen(s);
	res = ft_calloc(sizeof(char), len + 1);
	if (!res)
		return (NULL);
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
	free(*s);
	*s = removed;
}
