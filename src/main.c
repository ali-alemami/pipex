/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:43:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/13 18:36:27 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	if (argc < 6 && (argv[1] && !ft_strncmp(argv[1], "here_doc", 9)))
	{
		ft_putstr_fd("Error: missing arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex here_doc LIMITER cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit(1);
	}
	if (argc < 5)
	{
		ft_putstr_fd("Error: missing arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2\n", 2);
		exit(1);
	}
	argv_to_tokens(argc, argv);
	(void)envp;
	return (0);
}
