/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:57:56 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/18 18:12:04 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	make_stdin(t_cmd_list *head)
{
	int	fd;

	fd = open(head->content, O_RDONLY);
	if (fd == -1)
	{
		cmd_lstclear(head, free);
		perror("open infile");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		cmd_lstclear(head, free);
		close(fd);
		perror("dup2");
		exit(1);
	}
	close(fd);
}

static void	make_stdout(t_cmd_list *head, t_cmd_list *tail, char **envp)
{
	char	*cmd_path;
	int		fd;
	pid_t	pid;

	fd = open(tail->content, O_WRONLY);
	if (fd == -1)
	{
		cmd_lstclear(head, free);
		perror("open outfile");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		cmd_lstclear(head, free);
		close(fd);
		perror("dup2");
		exit(1);
	}
	close(fd);
	pid = fork();
	if (pid == -1)
	{
		cmd_lstclear(head, free);
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		cmd_path = get_directory(tail->prev->content, envp);
		if (!cmd_path)
		{
			cmd_lstclear(head, free);
			exit(1);
		}
		if (execve(cmd_path, (char *[]){tail->prev->content, NULL}, envp) == -1)
		{
			cmd_lstclear(head, free);
			free(cmd_path);
			perror("execve");
			exit(1);
		}
	}
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
		if (!cmd_path)
		{
			cmd_lstclear(head, free);
			exit(1);
		}
		if (execve(cmd_path, (char *[]){node->content, NULL}, envp) == -1)
		{
			cmd_lstclear(head, free);
			free(cmd_path);
			perror("execve");
			exit(1);
		}
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
