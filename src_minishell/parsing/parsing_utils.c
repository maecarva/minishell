/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:59:56 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/17 17:00:02 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

t_node2	*ptr_to_node(void *node)
{
	return ((t_node2 *)(node));
}

void padding ( char ch, int n ){
 
	for (int i = 0; i <= n; i++ )
		putchar ( ch );
}

void	print_node(t_btree *node)
{
	t_node2 *n = ptr_to_node(node->item);
	switch (n->type) {
		case PIPE_TOKEN:
			printf("PIPE \n");
		break ;
		case CMD:
			printf("COMMAND= {");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
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
			printf("ECHO ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case CD:
			printf("CD ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case PWD:
			printf("PWD ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case EXPORT:
			printf("EXPORT ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case UNSET:
			printf("UNSET ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case ENV:
			printf("ENV ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case EXIT:
			printf("EXIT ={");
			for (int i = 0; n->command[i]; i++) {
				printf(" [%s]", n->command[i]);
			}
			printf(" }\n");
		break ;
		case OR:
			printf("OR \n");
		break ;
		case AND:
			printf("AND \n");
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

