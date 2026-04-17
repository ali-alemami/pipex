/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 17:02:35 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/17 23:12:21 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	connector(int argc, char **argv, char **envp)
{
	t_cmd_list	*head;
	t_cmd_list	*tail;

	head = NULL;
	tail = NULL;
	argv_to_tokens(argc, argv, &head, &tail);
	main_loop(head, tail, envp);
	cmd_lstclear(&head, free);
}
