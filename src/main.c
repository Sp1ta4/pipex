/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:28:03 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/07 19:42:44 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	do_here_doc(char *limiter)
{
	
}


int	main(int argc, char **argv, char **envp)
{
	int	is_here_doc;
	int	infile;

	if (argc && argv)
	{
		is_here_doc = argv[1] == "here_doc";
		if (argc < 5)
			exit(2);
		if (is_here_doc)
		{
			infile = do_here_doc(argv[2]);
			argv[2] = infile;
			run_processes(argc - 1, argv + 2, envp);
		}
		else
			run_processes(argc - 1, argv + 1, envp);
	}
	return (0);
}
