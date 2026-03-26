/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:43:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/03/26 22:41:15 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error.\nUsage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	return (0);
}
