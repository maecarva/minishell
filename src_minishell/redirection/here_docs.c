/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebonutto <ebonutto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 16:40:51 by ebonutto          #+#    #+#             */
/*   Updated: 2025/02/25 11:03:44 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipes.h"

static void	create_hd(t_config *ms_data, t_btree *cmd, char *limiter)
{
	char	*line;
	int		fd_infile;

	fd_infile = open(((t_node2 *)(cmd->item))->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_infile == -1)
	{
		perror(((t_node2 *)(cmd->item))->file);
		ms_data->last_error_code = ERROR_CODE;
		clear_minishell(ms_data);
	}
	line = NULL;
	while (1)
	{
		if (get_next_line(0, &line) == -1)
		{
			perror("malloc");
			ft_close(&fd_infile);
			ms_data->last_error_code = ERROR_CODE;
			clear_minishell(ms_data);
		}
		if (ft_strncmp(line, limiter,
				ft_max(ft_strlen(limiter), ft_strlen(line))) == '\n')
		{
			free(line);
			ft_close(&fd_infile);
			return ;
		}
		ft_putstr_fd(line, fd_infile);
	}
}

void	get_name_here_doc(t_config *minishell, t_btree *cmd, int *i)
{
	char	*name;
	char	*number;

	number = ft_itoa(*i);
	if (!number)
	{
		minishell->last_error_code = ERROR_CODE;
		clear_minishell(minishell);
	}
	name = ft_strjoin("/tmp/here_doc_", number);
	if (!name)
	{
		free(number);
		minishell->last_error_code = ERROR_CODE;
		clear_minishell(minishell);
	}
	((t_node2 *)(cmd->item))->file = name;
	(*i)++;
}

void	find_here_doc(t_config *minishell, t_btree *cmd, int *i)
{
	char	*limiter;
	if (((t_node2 *)(cmd->item))->type == HEREDOC)
	{
		limiter = ((t_node2 *)(cmd->item))->file;
		get_name_here_doc(minishell, cmd, i);
		create_hd(minishell, cmd, limiter);
		free(limiter);
	}
}

void	btree_apply_prefix(t_config *ms_data, t_btree *root, int *i, void (*applyf)(t_config *minishell, t_btree *cmd, int *i))
{
	if (root == NULL)
		return ;
	applyf(ms_data, root, i);
	if (root->left)
		btree_apply_prefix(ms_data, root->left, i, applyf);
	if (root->right)
		btree_apply_prefix(ms_data, root->right, i, applyf);
}

void	get_here_docs(t_config *ms_data)
{
	int		i;

	i = 0;
	btree_apply_prefix(ms_data, ms_data->ast, &i, find_here_doc);
	ms_data->ast = ms_data->dont_fucking_touch_me;
}
