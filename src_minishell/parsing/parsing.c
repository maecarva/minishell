/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:59:56 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 12:50:08 by maecarva         ###   ########.fr       */
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
	t_node	*tmpnode;

	tmpnode = ft_calloc(sizeof(t_node), 1);
	tmpnode->type = PIPE;
	tmpnode->cmd = NULL;

	arbre = ft_btree_create_node(tmpnode);
	arbre->left = ft_btree_create_node(left());
	arbre->right = ft_btree_create_node(right());
	print_arbre(arbre);
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
		printf("tokenstr : '%s'\n", tokenstr_split[i]);
		i++;
	}
	return (tokenstr_split);
}

t_btree	*parse_cmd(char *cmd)
{
	int		num_token;
	t_btree	*arbre;
	char	**cmd_split;

	if (!cmd)
		return (NULL);
	num_token = count_tokens(cmd);
	if (num_token == 0)
		return (NULL);
	cmd_split = split_tokens(cmd, num_token);
	construct_ast(&arbre);
	return (arbre);
}
