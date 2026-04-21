/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:16:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/22 02:25:09 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>   // execve, fork
# include <sys/wait.h> // wait
# include <stdio.h>    // perror
# include <stdlib.h>   // exit
# include <fcntl.h>	   // open
# include "libft.h"

typedef enum s_tok_type
{
	infile,
	outfile,
	cmd,
	flags,
	here_doc
}	t_tok_type;

typedef struct s_cmd_list
{
	t_tok_type			type;
	char				*content;
	struct s_cmd_list	*next;
	struct s_cmd_list	*prev;
}						t_cmd_list;

//linked list
t_cmd_list	*cmd_lstnew(void *content);
void		cmd_lstclear(t_cmd_list **lst, void (*del)(void*));
t_cmd_list	*make_node(char *str, t_cmd_list **head, t_tok_type type);

//tokenization
int				is_flag(char *argv);
void			argv_to_tokens(int argc, char **argv,
				t_cmd_list **head, t_cmd_list **tail);

//path
char		*get_directory(char *cmd, char **envp);

//execution
void		clear_exit(t_cmd_list *head, char *error_message);
void		close_dup2(t_cmd_list *head, int fd_to_close, int fd_to_dup, int std);
void		execute_cmd(t_cmd_list *head, char *cmd, char **envp);
void		main_loop(t_cmd_list *head, t_cmd_list *tail, char **envp);

//connector
void		connector(int argc, char **argv, char **envp);

#endif