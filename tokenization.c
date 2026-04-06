/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:35:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/06 16:58:49 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	del(void *content)
{
	free(content);
}

void	tokenize_infile(char **argv, t_cmd_list **list)
{
	t_cmd_list	*tmp;
	
	tmp = *list;
	(*list) = cmd_lstnew(ft_strdup(argv[1]));
	if (!(*list))
	{
		cmd_lstclear(list, del);
		perror("malloc");
		exit(1);
	}
	(*list)->type = infile;
}

void	tokenize_outfile(char **argv, t_cmd_list **list)
{
	int	i;
	i = 0;
	while (argv[i])
		i++;
	i--;
	(*list) = cmd_lstnew(ft_strdup(argv[i]));
	if (!(*list))
	{
		cmd_lstclear(list, del);
		perror("malloc");
		exit(1);
	}
	(*list)->type = outfile;
}

static int	has_flag(char *argv)
{
	if (ft_strncmp(argv, "-", 1))
		return (1);
	return (0);
}

void	tokenize_flags(char *argv, t_cmd_list **list, int *i)
{
	(*list) = cmd_lstnew(ft_strdup(argv));
	if (!(*list))
	{
		cmd_lstclear(list, del);
		perror("malloc");
		exit(1);
	}
	(*list)->type = flags;
	(*list) = (*list)->next;
	(*i)++;
}

void	tokenize_cmds(char **argv, t_cmd_list **list)
{
	int	i;

	i = 1;
	while(argv[i + 1])
	{
		(*list) = cmd_lstnew(ft_strdup(argv[i]));
		if (!(*list))
		{
			cmd_lstclear(list, del);
			perror("malloc");
			exit(1);
		}
		(*list)->type = cmd;
		(*list) = (*list)->next;
		i++;
		if (has_flag(argv[i]))
			tokenize_flags(argv[i], list, &i);
	}
}

void	print_list(t_cmd_list *list)
{
	int		i;
	char	*str;
	printf("f\n");
	i = 0;
	while (list)
	{
		printf("statrt\n");
		if (list->type == infile)
			str = "infile";
		if (list->type == outfile)
			str = "outfile";
		if (list->type == cmd)
			str = "cmd";
		if (list->type == flags)
			str = "flags";
		ft_printf("index[%d]: %s\n", i, str);
		i++;
		list = list->next;
		printf("first\n");
	}
}

void	argv_to_tokens(char **argv)
{
	t_cmd_list	*head;
	t_cmd_list	*tail;
	t_cmd_list	*node;

	tokenize_infile(argv, &list);
	tokenize_cmds(argv, &list);
	tokenize_outfile(argv, &list);
	printf("content: %s\n", list->content);
	print_list(list);
}
