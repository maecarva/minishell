/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:55 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 14:54:04 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"
#include <stddef.h>
#include <stdio.h>

t_btree	*create_special_node(t_token nodetype)
{
	t_btree	*new_node;
	t_node	*node_content;

	node_content = ft_calloc(sizeof(t_node), 1);
	if (!node_content)
		return NULL;
	node_content->type = nodetype;
	node_content->cmd = NULL;
	new_node = ft_btree_create_node(node_content);
	if (!new_node)
		return (free(node_content), NULL);
	return (new_node);
}

void	redirection_left(t_cmd *cmd) // < entre.txt cat -e
{
	int		i;
	char	*tmp;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->cmd[i] && cmd->cmd[i] == '<')
		i++;
	if (cmd->cmd[i] == '\0') // "<" no infile
		return ;
	while (cmd->cmd[i] != '\0' && ft_isspace(cmd->cmd[i]))
		i++;
	if (ft_strlen(&cmd->cmd[i]))
	{
		// extract file name
		cmd->input_file = ft_strdup(&cmd->cmd[i]);
		if (!cmd->input_file)
			return ;
		i = 0;
		while (cmd->input_file[i] && !ft_isspace(cmd->input_file[i]))
			i++;
		ft_bzero(&cmd->input_file[i], ft_strlen(&cmd->input_file[i]));
		// edit cmd to delete "< infile"
		tmp = ft_strnstr(cmd->cmd, cmd->input_file, ft_strlen(cmd->cmd));
		if (!tmp)
			return ((void)printf("error while editing cmd.cmd in < redirection\n"));
		while (ft_isprint(*tmp) && !ft_isspace(*tmp))
			tmp++;
		while (ft_isspace(*tmp))
			tmp++;
		ft_bzero(cmd->cmd, tmp - cmd->cmd);
		ft_memmove(cmd->cmd, tmp, ft_strlen(tmp));
		ft_bzero(tmp, ft_strlen(tmp));
	}
	cmd->redirection = true;
}

void	redirection_right(t_cmd *cmd) // cat > outfile
{
	int	i;

	if (!cmd)
		return ;
	i = 0;
	while (cmd->cmd[i] != '\0' && cmd->cmd[i] != '>')
		i++;
	if (cmd->cmd[i] == '>')
		i++;
	while (cmd->cmd[i] != '\0' && ft_isspace(cmd->cmd[i]))
		i++;
	if (cmd->cmd[i] == '\0') // "cat >" (no outfile)
		return ;
	cmd->output_file = ft_strdup(&cmd->cmd[i]);
	if (!cmd->output_file)
		return ;
	i = ft_strchr(cmd->cmd, '>') - cmd->cmd;
	while ((size_t)i < ft_strlen(cmd->cmd))
		cmd->cmd[i++] = '\0';
	cmd->redirection = true;
}

void	here_doc(t_cmd *cmd)
{
	int	i;
	char	*needle_ptr;

	if (!cmd)
		return ;
	needle_ptr = ft_strnstr(cmd->cmd, HERE_DOC, ft_strlen(cmd->cmd));
	if (ft_strlen(needle_ptr) == 2)
		return ((void)printf("error here_doc\n"));
	i = 2;
	while (ft_isspace(needle_ptr[i]))
		i++;
	if (needle_ptr[i] == '\0')
		return ((void)printf("error here_doc 2\n"));
	cmd->identifier = ft_strdup(&needle_ptr[i]);
	if (!cmd->identifier)
		return ((void)printf("can't malloc identifier\n"));
	needle_ptr--;
	while (ft_isspace(*needle_ptr) && needle_ptr > cmd->cmd)
		needle_ptr--;
	ft_bzero(needle_ptr + 1, ft_strlen(needle_ptr + 1));
	cmd->here_doc = true;
}

void	handle_redirection(t_cmd *cmd)
{
	if (!cmd)
		return ;

	if (ft_strnstr(cmd->cmd, HERE_DOC, ft_strlen(cmd->cmd)))
		here_doc(cmd);
	else if (ft_strchr(cmd->cmd, '<'))
		redirection_left(cmd);
	else if (ft_strchr(cmd->cmd, '>'))
		redirection_right(cmd);
}

t_btree	*create_command_node(char **cmd_split)
{
	int		i;
	t_cmd	*cmd;
	t_node	*node_content;
	t_btree	*new_node;

	if (!cmd_split)
		return (NULL);
	i = 0;
	while (cmd_split[i] == NULL)
		i++;
	node_content = ft_calloc(sizeof(t_node), 1);
	if (!node_content)
		return NULL;
	node_content->type = COMMAND;
	cmd = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd)
		return (NULL);
	cmd->cmd = ft_strdup(cmd_split[i]);
	if (!cmd->cmd)
		return (free(cmd), NULL);
	cmd->quotes = false;

	handle_redirection(cmd);


	node_content->cmd = cmd;

	new_node = ft_calloc(sizeof(t_btree), 1);
	if (!new_node)
		return (free(cmd->cmd), free(cmd), NULL);
	new_node->item = node_content;
	return (new_node);
}
