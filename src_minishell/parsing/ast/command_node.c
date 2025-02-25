/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_node.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 15:50:44 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/21 15:05:07 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include_minishell/minishell.h"

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
		if (ptr_to_lexertoklist(tmp->content)->type >= TRUNCATE && ptr_to_lexertoklist(tmp->content)->type <= HEREDOC )
			redirtokcount[ptr_to_lexertoklist(tmp->content)->type - 1] += 1;
		tmp = tmp->next;
		if (tmp == start || tmp == end)
			break ;
	}
	return (total);
}

char	**extractcmd(t_dlist *start, t_dlist *end)
{
	int		i;
	int		totallen;
	t_dlist	*tmp;
	char	**cmd;
	char	*token;

	if (!start || !end)
		return (NULL);
	i = 0;
	totallen = 0;
	tmp = start;
	while (tmp)
	{
		token = ptr_to_lexertoklist(tmp->content)->token;
		if ((ptr_to_lexertoklist(tmp->content)->type == CMD || ptr_to_lexertoklist(tmp->content)->type == ARGS))
		{
			if (ft_strlen(token) == 0 && ptr_to_lexertoklist(tmp->content)->type == CMD)
				return (NULL);
			totallen++;
		}
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
	cmd = ft_calloc(sizeof(char *), totallen + 1);
	if (!cmd)
		return (NULL);
	tmp = start;
	i = 0;
	while (tmp)
	{
		token = ptr_to_lexertoklist(tmp->content)->token;
		if (ptr_to_lexertoklist(tmp->content)->type == CMD || ptr_to_lexertoklist(tmp->content)->type == ARGS)
		{
			cmd[i] = ft_strdup(token);
			clean_quotes(&cmd[i]);
			i++;
		}
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
	return (cmd);
}

void	add_left(t_btree *node, t_btree *new)
{
	t_btree	*tmp;

	tmp = node;
	while (tmp->left != NULL)
		tmp = tmp->left;
	tmp->left = new;
}

void	add_right(t_btree *node, t_btree *new)
{
	t_btree	*tmp;

	tmp = node;
	while (tmp->right != NULL)
		tmp = tmp->right;
	tmp->right = new;
}

void	handle_redirections(t_btree **node, t_dlist *start, t_dlist *end)
{
	t_btree	*tmpleft;
	t_dlist	*tmp;
	t_node2	*nodec;
	char	*tmpc;

	if (!(*node))
		return ;
	tmp = start;
	tmpc = NULL;
	while (tmp)
	{
		nodec = NULL;
		if (ptr_to_lexertoklist(tmp->content)->type >= TRUNCATE && ptr_to_lexertoklist(tmp->content)->type <= HEREDOC)
		{
			nodec = ft_calloc(sizeof(t_node2), 1);
			nodec->type = ptr_to_lexertoklist(tmp->content)->type;
			nodec->file = ft_strdup(ptr_to_lexertoklist(tmp->next->content)->token);
			clean_quotes(&nodec->file);
			tmpleft = ft_btree_create_node(nodec);
			add_left(*node, tmpleft);
			tmpleft = NULL;
			nodec = NULL;
		}
		if (tmp == end)
			break ;
		tmp = tmp->next;
	}
}

t_btree	*create_cmd_node(t_dlist *start, t_dlist *end)
{
	t_btree	*node;
	int		redirections[4]; // < << > >>
	t_lexertoklist	*redirtok[2]; // 0 : < <<, 1 : > >>
	t_node2	*nodecmdcontent;
	int		totalredir;

	totalredir = 0;
	if (!start || !end)
		return (NULL);
	ft_bzero(redirections, sizeof(int) * 4);
	count_token_type(start, end, redirections);
	totalredir = redirections[0] + redirections[1] + redirections[2] + redirections[3];
	ft_bzero(redirtok, sizeof(t_list *) * 2);
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
		handle_redirections(&node, start, end);
	return (node);
}
