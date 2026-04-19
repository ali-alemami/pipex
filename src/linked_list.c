/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:30:01 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/18 17:06:22 by aalemami         ###   ########.fr       */
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

static void	cmd_lstdelone(t_cmd_list *node, void (*del)(void *))
{
	if (!node || !del)
		return ;
	del(node->content);
	free(node);
}

void	cmd_lstclear(t_cmd_list **head, void (*del)(void*))
{
	t_cmd_list	*current;

	if (!head || !del)
		return ;
	while ((*head))
	{
		current = ((*head));
		(*head) = (*head)->next;
		cmd_lstdelone(current, del);
	}
}

t_cmd_list	*make_node(char *str, t_cmd_list **head, t_tok_type type)
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
