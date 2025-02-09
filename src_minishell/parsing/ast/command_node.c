/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:50:44 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/09 16:15:17 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

int	count_token_type(t_dlist *start, t_dlist *end, t_lexertok token)
{
	t_dlist	*tmp;
	int		total;

	total = 0;
	if (!start || !end)
		return (total);
	tmp = start;
	if (start == end && ptr_to_lexertoklist(tmp->content)->type == token)
		return (1);
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == token)
			total++;
		tmp = tmp->next;
		if (tmp == start || tmp == end)
			break ;
	}
	return (total);
}

char	*extract_command(t_dlist *start, t_dlist *end)
{
	int		i;
	int		totallen;
	t_dlist	*tmp;
	char	*cmd;

	if (!start || !end)
		return (NULL);
	i = 0;
	totallen = 0;
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == CMD && ptr_to_lexertoklist(tmp->content)->type == ARGS)
			totallen += ft_strlen(ptr_to_lexertoklist(tmp->content)->token) + 1;
		tmp = tmp->next;
		if (tmp == start || tmp == end)
			break ;
	}
	cmd = ft_calloc(sizeof(char), totallen + 1);
	if (!cmd)
		return (NULL);
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type == CMD && ptr_to_lexertoklist(tmp->content)->type == ARGS)
		{
			ft_strlcat(cmd, ptr_to_lexertoklist(tmp->content)->token, totallen);
			ft_strlcat(cmd, " ", totallen);
		}
		tmp = tmp->next;
		if (tmp == start || tmp == end)
			break ;
	}
	return (cmd);
}

t_btree	*create_cmd_node(t_dlist *start, t_dlist *end)
{
	t_btree	*node;
	// int		redirections[4]; // < << > >>
	t_list	*redirtok[2]; // 0 : < <<, 1 : > >>
	t_node2	*nodecmdcontent;

	if (!start || !end)
		return (NULL);
	// ft_bzero(redirections, sizeof(int) * 4);
	ft_bzero(redirtok, sizeof(t_list) * 2);
	node = ft_calloc(sizeof(t_btree), 1);
	if (!node)
		return (NULL);
	nodecmdcontent = ft_calloc(sizeof(t_node2), 1);
	if (!nodecmdcontent)
		return (free(node), NULL);

	nodecmdcontent->type = CMD;
	nodecmdcontent->command = extract_command(start, end);
	if (!nodecmdcontent->command)
		return (free(node), free(nodecmdcontent), NULL);
	node->item = nodecmdcontent;
	return (node);
}
