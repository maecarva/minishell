/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:59:56 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/07 09:35:53 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

t_node2	*ptr_to_node(void *node)
{
	return ((t_node2 *)(node));
}

// t_node	*left(void)
// {
// 	t_node	*n = ft_calloc(sizeof(t_node), 1);
// 	n->type = COMMAND;
// 	n->cmd = ft_calloc(sizeof(t_cmd), 1);
// 	n->cmd->cmd = "ls";
// 	n->cmd->quotes = false;
// 	return (n);
// }

// t_node	*right(void)
// {
// 	t_node	*n = ft_calloc(sizeof(t_node), 1);
// 	n->type = COMMAND;
// 	n->cmd = ft_calloc(sizeof(t_cmd), 1);
// 	n->cmd->cmd = "grep";
// 	n->cmd->quotes = false;
// 	return (n);
// }

void padding ( char ch, int n ){
 
	for (int i = 0; i <= n; i++ )
		putchar ( ch );
}

void	print_node(t_btree *node)
{
	t_node2 *n = ptr_to_node(node->item);
	switch (n->type) {
		case PIPE_TOKEN:
			printf("PIPE ");
		break ;
		case CMD:
			printf("COMMAND= ");
			printf("%s ", n->command);
			printf("\n");
		break ;
		case TRUNCATE:
			printf("TRUNCATE > ");
			printf("%s\n", n->file);
		break ;
		case REDIRECT_INPUT:
			printf("REDIR < ");
			printf("%s\n", n->file);
		break ;
		case APPEND:
			printf("APPEND >> ");
			printf("%s\n", n->file);
		break ;
		case HEREDOC:
			printf("HERE_DOC << ");
			printf("%s\n", n->file);
		break ;
		case ECHO:
			printf("ECHO ");
			printf("%s\n", n->command);
		break ;
		case CD:
			printf("CD ");
			printf("%s\n", n->command);
		break ;
		case PWD:
			printf("PWD ");
			printf("%s\n", n->command);
		break ;
		case EXPORT:
			printf("EXPORT ");
			printf("%s\n", n->command);
		break ;
		case UNSET:
			printf("UNSET ");
			printf("%s\n", n->command);
		break ;
		case ENV:
			printf("ENV ");
			printf("%s\n", n->command);
		break ;
		case EXIT:
			printf("EXIT ");
			printf("%s\n", n->command);
		break ;
		default:
			printf("WRONG TYPE ");
		break ;
	}
}

void	print_arbre(t_btree *root, int level)
{
	if ( root == NULL ) {
		padding ( '\t', level );
		printf("\n");
	} else {
		print_arbre( root->right, level + 1 );
		padding ( '\t', level );
		print_node(root);
		print_arbre( root->left, level + 1 );
	}
}

// command : ls -la | grep 'test'
// t_btree	*arbre_bidon()
// {
// 	t_btree	*arbre;
// 	t_node	*tmpnode;

// 	tmpnode = ft_calloc(sizeof(t_node), 1);
// 	tmpnode->type = PIPE;
// 	tmpnode->cmd = NULL;

// 	arbre = ft_btree_create_node(tmpnode);
// 	arbre->left = ft_btree_create_node(left());
// 	arbre->right = ft_btree_create_node(right());
// 	print_arbre(arbre, 0);
// 	return (arbre);
// }

