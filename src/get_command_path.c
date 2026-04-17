/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 12:13:56 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/17 16:35:35 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(envp[i]);
			if (!path)
			{
				perror("malloc");
				exit(1);
			}
			return (path);
		}
		i++;
	}
	ft_putstr_fd("path not found.\n", 2);
	exit(1);
}

static char	*concat_2char(char *str, char *s1, char *s2)
{
	char	*temp;
	char	*final;

	temp = ft_strjoin(&s1[0], &s2[0]);
	if (!temp)
		return (NULL);
	final = ft_strjoin(str, temp);
	free(temp);
	return (final);
}

static int	check_all_directories(char **directories, char *cmd, char **final)
{
	int	i;

	i = 0;
	while (directories[i])
	{
		*final = concat_2char(directories[i], "/", cmd);
		if (!(*final))
		{
			free_split(directories);
			perror("malloc");
			exit(1);
		}
		if (access(*final, X_OK) == 0)
		{
			free_split(directories);
			return (0);
		}
		free(*final);
		i++;
	}
	return (1);
}

char	*get_directory(char *cmd, char **envp)
{
	char	**directories;
	char	*final;
	char	*path;

	path = get_path(envp);
	directories = ft_split(path, ':');
	free(path);
	if (!directories)
	{
		perror("malloc");
		exit(1);
	}
	if (check_all_directories(directories, cmd, &final) == 0)
		return (final);
	free_split(directories);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	exit(1);
}
