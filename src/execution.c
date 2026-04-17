/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 22:57:56 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/17 23:12:34 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_stdin(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
	{
		perror("open infile");
		exit(1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

void	make_stdout(t_cmd_list *tail, char **envp)
{
	char	*cmd_path;
	int		fd;

	fd = open(tail->content, O_WRONLY);
	if (fd == -1)
	{
		perror("open outfile");
		exit(1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
	cmd_path = get_directory(tail->prev->content, envp);
	execve(cmd_path, (char *[]){tail->prev->content, NULL}, envp);
}

void	point_cmd_to_cmd(t_cmd_list *node, char **envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	char	*cmd_path;

	if (!node->next->next)
		return ;
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		cmd_path = get_directory(node->content, envp);
		execve(cmd_path, (char *[]){node->content, NULL}, envp);
	}
	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	point_cmd_to_cmd(node->next, envp);
}

void	main_loop(t_cmd_list *head, t_cmd_list *tail, char **envp)
{
	make_stdin(head->content);
	point_cmd_to_cmd(head->next, envp);
	make_stdout(tail, envp);
}
