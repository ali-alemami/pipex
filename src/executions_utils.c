/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 02:14:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/22 02:47:03 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_exit(t_cmd_list *head, char *error_message)
{
	cmd_lstclear(&head, free);
	perror(error_message);
	exit(1);
}

void	close_dup2(t_cmd_list *head, int fd_to_close, int fd_to_dup, int std)
{
	close(fd_to_close);
	if (dup2(fd_to_dup, std) == -1)
		clear_exit(head, "dup2");
	close(fd_to_dup);
}

void	execute_cmd(t_cmd_list *head, char *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = get_directory(cmd, envp);
	if (!cmd_path)
	{
		cmd_lstclear(&head, free);
		exit(1);
	}
	if (execve(cmd_path, (char *[]){cmd, NULL}, envp) == -1)
		clear_exit(head, "execve");
}
