/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:57:56 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/22 02:16:35 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	point_file_to_std(t_cmd_list *head, char *file_name,
	t_tok_type type, int open_mode)
{
	int	fd;

	fd = open(file_name, open_mode);
	if (fd == -1)
		clear_exit(head, "open");
	if (dup2(fd, type) == -1)
	{
		close(fd);
		clear_exit(head, "dup2");
	}
	close(fd);
}

static void	make_stdin(t_cmd_list *head)
{
	point_file_to_std(head, head->content, STDIN_FILENO, O_RDONLY);
}

static void	make_stdout(t_cmd_list *head, t_cmd_list *tail, char **envp)
{
	pid_t	pid;

	point_file_to_std(head, tail->content, STDOUT_FILENO, O_WRONLY);
	pid = fork();
	if (pid == -1)
		clear_exit(head, "fork");
	if (pid == 0)
		execute_cmd(head, tail->prev->content, envp);
	waitpid(pid, NULL, 0);
}

static void	point_cmd_to_cmd(t_cmd_list *head, t_cmd_list *node, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!node->next->next)
		return ;
	if (pipe(pipe_fd) == -1)
		clear_exit(head, "pipe");
	pid = fork();
	if (pid == -1)
		clear_exit(head, "fork");
	if (pid == 0)
	{
		close_dup2(head, pipe_fd[0], pipe_fd[1], STDOUT_FILENO);
		execute_cmd(head, node->content, envp);
	}
	waitpid(pid, NULL, 0);
	close_dup2(head, pipe_fd[1], pipe_fd[0], STDIN_FILENO);
	point_cmd_to_cmd(head, node->next, envp);
}

void	main_loop(t_cmd_list *head, t_cmd_list *tail, char **envp)
{
	make_stdin(head);
	point_cmd_to_cmd(head, head->next, envp);
	make_stdout(head, tail, envp);
}
