/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:43:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/03/27 15:59:06 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>   // execve, fork
#include <sys/wait.h> // wait
#include <stdio.h>    // perror
#include <stdlib.h>   // exit
#include "libft.h"

void	execute_command(void)
{
	pid_t	pid;
	char	*args[3] = {"ls", "-la", NULL};
	
	pid = fork();
	if (pid == 0)
	{
		execve("/usr/bin/ls", args, NULL);
		perror("execve failed");
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else
	{
		perror("fork failed");
	}
}

int	find_command(char *cmd, char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(cmd, envp[i], ft_strlen(cmd)) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 5)
	{
		ft_putstr_fd("Error.\nUsage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	execute_command();
	//char *cmd;
	return (0);
}
