/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:35:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/23 22:56:35 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	tokenize_input(char *argv, t_cmd_list **head, t_cmd_list **tail, t_tok_type type)
{
	t_cmd_list	*node;

	node = make_node(argv, head, type);
	(*head) = node;
	(*tail) = node;
}

static void	tokenize_outfile(char *argv, t_cmd_list **head, t_cmd_list **tail)
{
	t_cmd_list	*node;
	t_cmd_list	*temp;

	temp = (*tail);
	node = make_node(argv, head, outfile);
	(*tail)->next = node;
	(*tail) = node;
	(*tail)->prev = temp;
}

static void	tokenize_flags(char *argv, t_cmd_list **head, t_cmd_list **tail)
{
	t_cmd_list	*node;
	t_cmd_list	*temp;

	temp = (*tail);
	node = make_node(argv, head, flags);
	(*tail)->next = node;
	(*tail) = node;
	(*tail)->prev = temp;
}

static void	tokenize_cmds(char **argv, t_cmd_list **head, t_cmd_list **tail)
{
	t_cmd_list	*node;
	int			i;

	i = 2;
	while (argv[i + 1])
	{
		node = make_node(argv[i], head, cmd);
		(*tail)->next = node;
		(*tail) = node;
		i++;
		while (is_flag(argv[i]) && argv[i + 1])
		{
			tokenize_flags(argv[i], head, tail);
			i++;
		}
	}
}

// void	print_list(t_cmd_list *list)
// {
// 	int		i;
// 	char	*str;
// 	i = 0;
// 	while (list)
// 	{
// 		if (list->type == infile)
// 			str = "infile";
// 		else if (list->type == outfile)
// 			str = "outfile";
// 		else if (list->type == cmd)
// 			str = "cmd";
// 		else if (list->type == flags)
// 			str = "flags";
// 		else if (list->type == here_doc)
// 			str = "here_doc";
// 		else
// 			str = "unknown";
// 		ft_printf("index[%d]: %s\n", i, str);
// 		i++;
// 		list = list->next;
// 	}
// }

void	argv_to_tokens(int argc, char **argv,
	t_cmd_list **head, t_cmd_list **tail)
{
	if (ft_strncmp(argv[1], "here_doc", 9) != 0)
		tokenize_input(argv[1], head, tail, infile);
	else
		tokenize_input(argv[1], head, tail, here_doc);
	tokenize_cmds(argv, head, tail);
	tokenize_outfile(argv[argc - 1], head, tail);
}
