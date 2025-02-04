/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:59:56 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 12:25:48 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

t_node	*ptr_to_node(void *node)
{
	return ((t_node *)(node));
}

t_node	*left(void)
{
	t_node	*n = ft_calloc(sizeof(t_node), 1);
	n->type = COMMAND;
	n->cmd = ft_calloc(sizeof(t_cmd), 1);
	n->cmd->cmd = "ls";
	n->cmd->arguments = ft_lstnew("-la");
	n->cmd->flags = NULL;
	n->cmd->quotes = false;
	return (n);
}

t_node	*right(void)
{
	t_node	*n = ft_calloc(sizeof(t_node), 1);
	n->type = COMMAND;
	n->cmd = ft_calloc(sizeof(t_cmd), 1);
	n->cmd->cmd = "grep";
	n->cmd->arguments = ft_lstnew("'test'");
	n->cmd->flags = NULL;
	n->cmd->quotes = false;
	return (n);
}

void	print_arbre(t_btree *arbre)
{
	printf("\t\t\t\t\tnode : type = %s\n", ptr_to_node(arbre->item)->type == PIPE ? "PIPE" : "ERROR");
	printf("\t\tleft :\ntype = %s, cmd = %s, args = %s\n", ptr_to_node(arbre->left->item)->type == COMMAND ? "COMMAND" : "ERROR", ptr_to_node(arbre->left->item)->cmd->cmd, (char *)ptr_to_node(arbre->left->item)->cmd->arguments->content  );
	printf("\t\tright :\ntype = %s, cmd = %s, args = %s\n", ptr_to_node(arbre->right->item)->type == COMMAND ? "COMMAND" : "ERROR", ptr_to_node(arbre->right->item)->cmd->cmd, (char *)ptr_to_node(arbre->right->item)->cmd->arguments->content  );
}

// command : ls -la | grep 'test'
t_btree	*arbre_bidon()
{
	t_btree	*arbre;
	// t_node	*tmpnode;

	// tmpnode = ft_calloc(sizeof(t_node), 1);
	// tmpnode->type = PIPE;
	// tmpnode->cmd = NULL;

	arbre = ft_btree_create_node("|");
	arbre->left = ft_btree_create_node("grep e");
	arbre->right = ft_btree_create_node("cat");
	//print_arbre(arbre);
	return (arbre);
}
