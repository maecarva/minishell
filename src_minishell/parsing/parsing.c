/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:59:56 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/06 18:36:21 by ebonutto         ###   ########.fr       */
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
	n->cmd->quotes = false;
	return (n);
}

t_node	*right(void)
{
	t_node	*n = ft_calloc(sizeof(t_node), 1);
	n->type = COMMAND;
	n->cmd = ft_calloc(sizeof(t_cmd), 1);
	n->cmd->cmd = "grep";
	n->cmd->quotes = false;
	return (n);
}

void padding ( char ch, int n ){
 
	for (int i = 0; i <= n; i++ )
		putchar ( ch );
}

void	print_node(t_btree *node)
{
	t_node *n = ptr_to_node(node->item);
	switch (n->type) {
		case PIPE:
			printf("PIPE ");
		break ;
		case COMMAND:
			printf("COMMAND= ");
			printf("%s ", n->cmd->cmd);
			if (n->cmd->redirection)
			{
				if (n->cmd->input_file != NULL)
					printf("(infile : %s)\n", n->cmd->input_file);
				else
					printf("(outfile : %s)\n", n->cmd->output_file);
			}
			else if (n->cmd->here_doc)
				printf("(here_doc : %s)\n", n->cmd->identifier);
			else
				printf("\n");
		break ;
		default:
			printf("WRONG TYPE ");
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
t_btree	*arbre_bidon()
{
	t_btree	*arbre;
	t_node	*tmpnode;

	tmpnode = ft_calloc(sizeof(t_node), 1);
	tmpnode->type = PIPE;
	tmpnode->cmd = NULL;

	arbre = ft_btree_create_node(tmpnode);
	arbre->left = ft_btree_create_node(left());
	arbre->right = ft_btree_create_node(right());
	print_arbre(arbre, 0);
	return (arbre);
}

// ---------------------------------------------------------------- real parsing ------------------------------------------------------------ //


// count tokens

bool	is_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (true);
		i++;
	}
	return (false);
}

int	count_tokens(char *cmd)
{
	int		i;
	int		tokens;
	char	**splited_cmd;

	splited_cmd = ft_split(cmd, ' ');
	if (!splited_cmd)
		return (1);
	tokens = 0;
	i = 0;
	while (splited_cmd[i])
	{
		if (!is_in_charset(splited_cmd[i][0], SPECIALS_TOKEN))
		{
			tokens++;
			while (splited_cmd[i] && !is_in_charset(splited_cmd[i][0], SPECIALS_TOKEN))
				i++;
			continue ;
		}
		else
			tokens++;
		i++;
	}
	ft_free_double_ptr(&splited_cmd);
	return (tokens);
}

// create tokenstr

void	skip_token(char **cmd)
{
	if (!(*cmd))
		return ;
	if (is_in_charset(**cmd, SPECIALS_TOKEN))
		(*cmd)++;
	else
		while ((**cmd) != '\0' && !is_in_charset(**cmd, SPECIALS_TOKEN))
			(*cmd)++;
}

char	*get_token(char *cmd)
{
	int		size;
	int		i;
	char	*token;
	char	*trimtoken;

	i = -1;
	size = 0;
	if (is_in_charset(*cmd, SPECIALS_TOKEN))
	{
		token = ft_calloc(sizeof(char), 2);
		if (!token)
			return (NULL);
		*token = *cmd;
	}
	else
	{
		while (cmd[size] != '\0' && !is_in_charset(cmd[size], SPECIALS_TOKEN))
			size++;
		token = ft_calloc(sizeof(char), size + 1);
		if (!token)
			return (NULL);
		while (++i < size)
			token[i] = cmd[i];
	}
	trimtoken = ft_strtrim(token, WHITESPACES);
	free(token);
	return (trimtoken);
}

char	*extract_tokenstr(char	*cmd, int tokenindex)
{
	int		current_index;

	current_index = 0;
	while (*cmd != '\0' && current_index < tokenindex)
	{
		skip_token(&cmd);
		current_index++;
	}
	return (get_token(cmd));
}

// EXTRACT char *cmd into char **tokenstr_split
char	**split_tokens(char *cmd, int num_token)
{
	char	**tokenstr_split;
	int	i;

	i = 0;
	tokenstr_split = ft_calloc(sizeof(char *), num_token + 1);
	if (!tokenstr_split)
		return (NULL);
	while (i < num_token)
	{
		tokenstr_split[i] = extract_tokenstr(cmd, i);
		i++;
	}
	return (tokenstr_split);
}

int	cmd_split_len(char **cmd_split)
{
	int	i;

	i = 0;
	while (cmd_split[i] != NULL)
		i++;
	return (i);
}

t_btree	*parse_cmd(char *cmd)
{
	int		num_token;
	t_btree	*arbre;
	char	**cmd_split;
	int		cmd_len;

	arbre = NULL;
	if (!cmd)
		return (NULL);
	num_token = count_tokens(cmd);
	if (num_token == 0)
		return (NULL);
	cmd_split = split_tokens(cmd, num_token);
	if (!cmd_split)
		return (NULL);
	cmd_len = cmd_split_len(cmd_split);
	construct_ast(&arbre, cmd_split, cmd_len);
	//print_arbre(arbre, 0);
	free(cmd_split);
	return (arbre);
}
