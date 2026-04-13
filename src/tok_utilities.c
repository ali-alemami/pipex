/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utilities.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 18:49:49 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/13 18:56:17 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	has_flag(char *argv)
{
	if (!ft_strncmp(argv, "-", 1))
		return (1);
	return (0);
}

void	tokenize_heredoc(char *argv, t_cmd_list **head, t_cmd_list **tail)
{
	t_cmd_list	*node;

	node = make_node(argv, head, here_doc);
	(*head) = node;
	(*tail) = node;
}

void	tokenize_infile(char *argv, t_cmd_list **head, t_cmd_list **tail)
{
	t_cmd_list	*node;

	node = make_node(argv, head, infile);
	(*head) = node;
	(*tail) = node;
}
