/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:50:44 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 20:39:19 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

void	add_left(t_btree *node, t_btree *new)
{
	t_btree	*tmp;

	tmp = node;
	while (tmp->left != NULL)
		tmp = tmp->left;
	tmp->left = new;
}

void	handle_redirs(t_btree **node, t_dlist *start, t_dlist *end)
{
	t_dlist	*tmp;
	t_node2	*nodec;

	if (!(*node))
		return ;
	tmp = start;
	while (tmp)
	{
		if (ptr_to_lexertoklist(tmp->content)->type >= TRUNCATE
			&& ptr_to_lexertoklist(tmp->content)->type <= HEREDOC)
		{
			nodec = ft_calloc(sizeof(t_node2), 1);
			if (!nodec)
				break ;
			nodec->type = ptr_to_lexertoklist(tmp->content)->type;
			nodec->file = ft_strdup(
					ptr_to_lexertoklist(tmp->next->content)->token);
			clean_quotes(&nodec->file);
			add_left(*node, ft_btree_create_node(nodec));
			nodec = NULL;
		}
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
}

// int		redirs[4]; // < << > >>
t_btree	*create_cmd_node(t_dlist *start, t_dlist *end)
{
	t_btree	*node;
	int		redirs[4];
	t_node2	*nodecmdcontent;
	int		totalredir;

	totalredir = 0;
	if (!start || !end)
		return (NULL);
	ft_bzero(redirs, sizeof(int) * 4);
	count_token_type(start, end, redirs);
	totalredir = redirs[0] + redirs[1] + redirs[2] + redirs[3];
	node = ft_calloc(sizeof(t_btree), 1);
	if (!node)
		return (NULL);
	nodecmdcontent = ft_calloc(sizeof(t_node2), 1);
	if (!nodecmdcontent)
		return (free(node), NULL);
	nodecmdcontent->type = CMD;
	nodecmdcontent->command = extractcmd(start, end);
	if (!nodecmdcontent->command)
		return (free(node), free(nodecmdcontent), NULL);
	node->item = nodecmdcontent;
	if (totalredir >= 0)
		handle_redirs(&node, start, end);
	return (node);
}
