/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:35:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/05 15:42:30 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	del(void *content)
{
	free(content);
}

void	tokenize_infile(char **argv, t_cmd_list *list)
{
	list = cmd_lstnew(ft_strdup(argv[1]));
	if (!list)
	{
		cmd_lstclear(&list, del);
		perror("malloc");
		exit(1);
	}
	list->type = infile;
	list = list->next;
}

int	has_flag(char **argv)
{
	
}

void	tokenize_cmds(char **argv, t_cmd_list *list)
{
	int	i;

	i = 1;
	while(argv[i])
	{
		list = cmd_lstnew(ft_strdup(argv[i]));
		if (!list)
		{
			cmd_lstclear(&list, del);
			perror("malloc");
			exit(1);
		}
		list->type = cmd;
		list = list->next;
	}
}

void	argv_to_tokens(char **argv)
{
	t_cmd_list	*list;

	tokenize_infile(argv, list);
	tokenize_cmds(argv, list);
	//tokenize_outfile(argv, list);
}
