/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:16:16 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/03 15:54:19 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>   // execve, fork
# include <sys/wait.h> // wait
# include <stdio.h>    // perror
# include <stdlib.h>   // exit
# include "libft.h"

typedef enum e_tok_type
{
	infile,
	outfile,
	// pipe
	cmd,
	flags
}	t_tok_type;

typedef struct s_tok_list
{
	t_tok_type			type;
	char				*content;
	struct s_tok_list 	*next;
}						t_tok_list;

char	*get_directory(char *cmd, char **envp);
void	execute_cmd(char *dir, char *flags, char **envp);

#endif