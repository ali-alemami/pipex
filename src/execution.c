/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:57:56 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/20 01:56:24 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	point_file_to_std(t_cmd_list *head, char *file_name,
	t_tok_type type, int open_mode)
{
	int	fd;

	fd = open(file_name, open_mode);
	if (fd == -1)
	{
		cmd_lstclear(head, free);
		perror("open infile");
		exit(1);
	}
	if (dup2(fd, type) == -1)
	{
		cmd_lstclear(head, free);
		close(fd);
		perror("dup2");
		exit(1);
	}
	close(fd);
}

static void	execute_cmd(t_cmd_list *head, char *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = get_directory(cmd, envp);
	if (!cmd_path)
	{
		cmd_lstclear(head, free);
		exit(1);
	}
	if (execve(cmd_path, (char *[]){cmd, NULL}, envp) == -1)
	{
		cmd_lstclear(head, free);
		free(cmd_path);
		perror("execve");
		exit(1);
	}
}

static void	make_stdin(t_cmd_list *head)
{
	point_file_to_std(head, head->content, stdin, 00);
}

static void	make_stdout(t_cmd_list *head, t_cmd_list *tail, char **envp)
{
	char	*cmd_path;
	pid_t	pid;

	point_file_to_std(head, tail->content, stdout, 01);
	pid = fork();
	if (pid == -1)
	{
		cmd_lstclear(head, free);
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		execute_cmd(head, tail->prev->content, envp);
	waitpid(pid, NULL, 0);
	free(cmd_path);
}

static void	point_cmd_to_cmd(t_cmd_list *head, t_cmd_list *node, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*cmd_path;

	if (!node->next->next)
		return ;
	if (pipe(pipe_fd) == -1)
	{
		cmd_lstclear(head, free);
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		cmd_lstclear(head, free);
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		cmd_path = get_directory(node->content, envp);
		execute_cmd(head, node->content, envp);
	}
	free(cmd_path);
	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	point_cmd_to_cmd(head, node->next, envp);
}

void	main_loop(t_cmd_list *head, t_cmd_list *tail, char **envp)
{
	make_stdin(head);
	point_cmd_to_cmd(head, head->next, envp);
	make_stdout(head, tail, envp);
}
