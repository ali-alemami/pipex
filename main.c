/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:43:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/07 16:33:08 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"




int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	argv_to_tokens(argc, argv);
	return (0);
}
