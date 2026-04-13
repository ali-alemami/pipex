/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:30:01 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/13 18:48:28 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd_list	*cmd_lstnew(void *content)
{
	t_cmd_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->next = NULL;
	return (new_node);
}

static void	cmd_lstdelone(t_cmd_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

void	cmd_lstclear(t_cmd_list **lst, void (*del)(void*))
{
	t_cmd_list	*current;

	if (!lst || !del)
		return ;
	while ((*lst))
	{
		current = ((*lst));
		(*lst) = (*lst)->next;
		cmd_lstdelone(current, del);
	}
}

t_cmd_list	*make_node(char *str, t_cmd_list **head, e_tok_type type)
{
	t_cmd_list	*node;
	char		*content;

	content = ft_strdup(str);
	node = cmd_lstnew(content);
	if (!node || !content)
	{
		free(content);
		free(node);
		cmd_lstclear(head, free);
		perror("malloc");
		exit(1);
	}
	node->type = type;
	return (node);
}
