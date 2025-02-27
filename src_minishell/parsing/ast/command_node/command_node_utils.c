/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:29:57 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 20:47:43 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

int	count_token_type(t_dlist *start, t_dlist *end, int	*redirtokcount)
{
	t_dlist	*tmp;
	int		total;

	total = 0;
	if (!start || !end)
		return (total);
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type >= TRUNCATE
			&& ptr_to_lexertoklist(tmp->content)->type <= HEREDOC)
			redirtokcount[ptr_to_lexertoklist(tmp->content)->type - 1] += 1;
		tmp = tmp->next;
		if (tmp == start || tmp == end)
			break ;
	}
	return (total);
}

char	**get_cmd_array(t_dlist *start, t_dlist *end)
{
	int		totallen;
	t_dlist	*tmp;
	char	**cmd;
	char	*token;

	tmp = start;
	totallen = 0;
	while (tmp)
	{
		token = ptr_to_lexertoklist(tmp->content)->token;
		if ((ptr_to_lexertoklist(tmp->content)->type == CMD
				|| ptr_to_lexertoklist(tmp->content)->type == ARGS))
		{
			if (ft_strlen(token) == 0
				&& ptr_to_lexertoklist(tmp->content)->type == CMD)
				return (NULL);
			totallen++;
		}
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
	cmd = ft_calloc(sizeof(char *), totallen + 1);
	return (cmd);
}

void	populate_cmd_array(t_dlist *start, t_dlist *end, char ***cmd)
{
	int		i;
	t_dlist	*tmp;
	char	*token;

	tmp = start;
	i = 0;
	while (tmp)
	{
		token = ptr_to_lexertoklist(tmp->content)->token;
		if (ptr_to_lexertoklist(tmp->content)->type == CMD
			|| ptr_to_lexertoklist(tmp->content)->type == ARGS)
		{
			(*cmd)[i] = ft_strdup(token);
			if ((*cmd)[i] == NULL)
				break ;
			clean_quotes(&(*cmd)[i]);
			i++;
		}
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
}

char	**extractcmd(t_dlist *start, t_dlist *end)
{
	char	**cmd;

	if (!start || !end)
		return (NULL);
	cmd = get_cmd_array(start, end);
	if (!cmd)
		return (NULL);
	populate_cmd_array(start, end, &cmd);
	return (cmd);
}
