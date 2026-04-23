/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 02:14:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/22 18:44:59 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear_exit(t_cmd_list *head, char *error_message, char *free_str)
{
	free(free_str);
	cmd_lstclear(&head, free);
	perror(error_message);
	exit(1);
}

void	close_dup2(t_cmd_list *head, int fd_to_close, int fd_to_dup, int std)
{
	close(fd_to_close);
	if (dup2(fd_to_dup, std) == -1)
		clear_exit(head, "dup2", NULL);
	close(fd_to_dup);
}

void	execute_cmd(t_cmd_list *head, t_cmd_list *node, char **envp)
{
	char	*cmd_path;
	char	**cmd_argv;

	cmd_path = get_directory(node->content, envp);
	if (!cmd_path)
	{	
		cmd_lstclear(&head, free);
		exit(1);
	}
	cmd_argv = ft_arr_push(NULL, node->content);
	if (!cmd_argv)
	{
		clear_exit(head, "malloc", cmd_path);
	}
	if (is_flag(node->next->content))
	{
		cmd_argv = ft_arr_push(cmd_argv, node->next->content);
		if (!cmd_argv)
			clear_exit(head, "malloc", cmd_path);
	}
	if (execve(cmd_path, cmd_argv, envp) == -1)
	{
		ft_free_split(cmd_argv);
		clear_exit(head, "execve", cmd_path);
	}
}

void	child_failure(t_cmd_list *head, int pipe_fd[2], int status)
{
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		cmd_lstclear(&head, free);
		exit(WEXITSTATUS(status));
	}
}