/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:16:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/13 18:56:32 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>   // execve, fork
# include <sys/wait.h> // wait
# include <stdio.h>    // perror
# include <stdlib.h>   // exit
# include "libft.h"

typedef enum s_tok_type
{
	infile,
	outfile,
	cmd,
	flags,
	here_doc
}	e_tok_type;

typedef struct s_cmd_list
{
	e_tok_type			type;
	char				*content;
	struct s_cmd_list	*next;
}						t_cmd_list;


//linked list
t_cmd_list	*cmd_lstnew(void *content);
void		cmd_lstclear(t_cmd_list **lst, void (*del)(void*));
t_cmd_list	*make_node(char *str, t_cmd_list **head, e_tok_type type);


//tokenization
int		has_flag(char *argv);
void	tokenize_heredoc(char *argv, t_cmd_list **head, t_cmd_list **tail);
void	tokenize_infile(char *argv, t_cmd_list **head, t_cmd_list **tail);
void	tokenize_outfile(char *argv, t_cmd_list **head, t_cmd_list **tail);
void	tokenize_flags(char *argv, t_cmd_list **head, t_cmd_list **tail);
void	tokenize_cmds(char **argv, t_cmd_list **head, t_cmd_list **tail);
void	argv_to_tokens(int argc, char **argv);


#endif