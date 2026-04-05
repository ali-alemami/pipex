/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 13:30:01 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/05 15:18:50 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd_list	*	cmd_lstnew(void *content)
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
		ft_lstdelone(current, del);
	}
}
