/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:20:55 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/04 18:23:08 by ebonutto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include_minishell/minishell.h"

int	count_char_in_str(char *str, int c)
{
	int	count;

	count = 0;
	if (!str)
		return (count);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char	*extract_infile(char **cmd, int *start_index) // "< infile1 (cat) < infile2 < infile3"
{
	int		i;
	char	*infile;
	char	*tmp;

	tmp = *cmd;
	i = *start_index;
	while (tmp[i] != '\0' && tmp[i] != '<')
		i++;
	if (tmp[i] == '\0')
		return (NULL);
	i++;
	while (ft_isspace(tmp[i]))
		i++;
	tmp = &(tmp[i]); // *cmd = "infile1 (cat) < infile2 < infile3"
	i = 0;
	while (tmp[i] && !ft_isspace(tmp[i]))
		i++;
	infile = ft_calloc(sizeof(char), i + 1);
	ft_strlcpy(infile, tmp, i + 1);
	*start_index = ((&tmp[i]) - *cmd);
	return (infile);
}

void	populate_infiles(char *cmd, char ***infile_list, int total_infile)
{
	int	i;
	int	start_index;

	start_index = 0;
	i = 0;
	while (i < total_infile)
	{
		(*infile_list)[i] = extract_infile(&cmd, &start_index);
		if ((*infile_list)[i] == NULL)
			return ((void)ft_free_double_ptr(infile_list));
		i++;
	}
}

char	*extract_command(char *cmd)
{
	int		i;
	char	**splited;
	int		cmdlen;
	int		start;
	char	*parsed_cmd;
	int		total_len;

	i = 0;
	cmdlen = 0;
	splited = ft_split(cmd, ' ');
	start = -1;
	total_len = 0;
	if (!splited)
		return (NULL);
	while (splited[i])
	{
		if (!ft_strchr(splited[i], '<') && i == 0)
		{
			start = i;
			total_len += ft_strlen(splited[i]);
			cmdlen++;
		}
		else if (i > 0 && !ft_strchr(splited[i], '<') && !ft_strchr(splited[i - 1], '<'))
		{
			if (start == -1)
				start = i;
			total_len += ft_strlen(splited[i]);
			cmdlen++;
		}
		i++;
	}
	
	parsed_cmd = ft_calloc(sizeof(char), total_len + 1 + (cmdlen - 1));
	if (!parsed_cmd)
		return (ft_free_double_ptr(&splited), NULL);
	while (!ft_strchr(splited[start], '<'))
	{
		ft_strlcat(parsed_cmd, splited[start], (total_len + 1 + cmdlen - 1));
		ft_strlcat(parsed_cmd, " ", (total_len + 1 + cmdlen - 1));
		start++;
	}
	return (ft_free_double_ptr(&splited), parsed_cmd);
}

void	redirection_left(t_cmd *cmd) // < entre.txt cat -e
{
	int		i;
	char	*tmp;
	int		total_infile;
	char	**infile_list;
	char	*extracted_cmd;

	if (!cmd)
		return ;
	i = 0;
	tmp = NULL;
	extracted_cmd = NULL;
	total_infile = count_char_in_str(cmd->cmd, R_LEFTCHAR);
	infile_list = ft_calloc(sizeof(char *), total_infile + 1);
	if (!infile_list)
		return ((void)printf("error malloc in redirection_left\n"));
	populate_infiles(cmd->cmd, &infile_list, total_infile);
	extracted_cmd = extract_command(cmd->cmd);
	free(cmd->cmd);
	cmd->cmd = extracted_cmd;
	cmd->redirection = true;
	cmd->input_file = infile_list;
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
