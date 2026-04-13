/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 13:11:07 by aalemami          #+#    #+#             */
/*   Updated: 2026/03/30 16:16:59 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_cmd(char *dir, char *flags, char **envp)
{
	pid_t	pid;
	char	**argv;

	argv = malloc(sizeof(char*) * 3);
	argv[0] = ft_strdup(dir);
	argv[1] = ft_strdup(flags);
	argv[2] = NULL;
	pid = fork();
	if (pid == 0)
	{
		execve(dir, argv, envp);
		free(dir);
		perror("execve");
	}
	wait(NULL);
}
