/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalemami <aalemami@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:35:45 by aalemami          #+#    #+#             */
/*   Updated: 2026/04/03 17:53:09 by aalemami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argv_to_tokens(char **argv)
{
	
	
	//argv
	//list of tokens
	// infile, cmd , flag, pipe, cmd ,flag , outfile?
	//approve!
	//we dont need a liked list, we already know that the maximum element are 6,
	//but bonus require multiple pipes os we need an infinite linked list
	//what we can make is a linked list consists of multiple 6 array items, 
	// each array has (infile cmd flags outfile)
	// so we have to make a function that reads arguments and splits them, 
	//
	//so big linked list, it has an array: (infile cmd flags outfile) and weather its first or not (out to pipe)
	// we will work with argv bcs we will not edit it;
	
}

void	execute(list)
{

}