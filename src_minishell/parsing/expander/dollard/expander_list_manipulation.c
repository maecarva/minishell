/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_list_manipulation.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maecarva <maecarva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:07:42 by maecarva          #+#    #+#             */
/*   Updated: 2025/02/26 18:52:20 by maecarva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include_minishell/minishell.h"

t_dlist	*create_arg_list(char	**files, t_dlist *before)
{
	t_dlist			*lst;
	int				i;
	t_lexertoklist	*tmp;

	if (!files || !*files || !before)
		return (NULL);
	i = 0;
	lst = NULL;
	tmp = NULL;
	while (files[i])
	{
		tmp = ft_calloc(sizeof(t_lexertoklist), 1);
		if (!tmp)
			return (dll_clear(&lst), NULL);
		tmp->token = ft_strdup(files[i]);
		if (i == 0)
			tmp->type = ptr_to_lexertoklist(before->content)->type;
		else
			tmp->type = ARGS;
		dll_add_back(&lst, dll_new(tmp));
		tmp = NULL;
		i++;
	}
	return (lst);
}

void	suppress1(t_dlist **lst)
{
	t_dlist	*before;
	t_dlist	*tmp;

	before = (*lst)->prev;
	tmp = (*lst);
	tmp->next = tmp;
	tmp->prev = tmp;
	before->prev = before;
	before->next = before;
	free_token_list(&tmp);
	*lst = before;
}

void	suppress2(t_dlist **lst)
{
	t_dlist	*before;
	t_dlist	*after;
	t_dlist	*tmp;

	before = (*lst)->prev;
	after = (*lst)->next;
	tmp = (*lst);
	tmp->next = tmp;
	tmp->prev = tmp;
	before->next = after;
	after->prev = before;
	*lst = after;
	free_token_list(&tmp);
}

void	suppress_element(t_dlist **lst)
{
	if (!lst || !*lst)
		return ;
	if (dll_size(lst) == 1)
		free_token_list(lst);
	else if (dll_size(lst) == 2)
		suppress1(lst);
	else
		suppress2(lst);
}

void	delete_token_invalid_var(t_dlist **tmp, t_dlist **tmp2)
{
	*tmp2 = *tmp;
	(*tmp)->prev->next = (*tmp)->next;
	(*tmp2)->next->prev = (*tmp2)->prev;
}
