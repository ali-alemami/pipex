/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:16:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/05 15:13:36 by aalemami         ###   ########.fr       */
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
	// pipe
	cmd,
	flags
}	e_tok_type;

typedef struct s_cmd_list
{
	e_tok_type			type;
	char				*content;
	struct s_cmd_list	*next;
}						t_cmd_list;

char	*get_directory(char *cmd, char **envp);
void	execute_cmd(char *dir, char *flags, char **envp);


//linked list
t_cmd_list	*cmd_lstnew(void *content);
void		cmd_lstclear(t_cmd_list **lst, void (*del)(void*));

#endif