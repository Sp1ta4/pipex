/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:28:03 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/11 15:34:50 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exit_print_model(void)
{
	const char	*msg1;
	const char	*msg2;

	msg1 = "Error: Insufficient arguments.\n";
	msg2 = "Usage: ./pipex infile command1 command2 outfile\n";
	write(2, msg1, ft_strlen(msg1));
	write(2, msg2, ft_strlen(msg2));
	exit(2);
}

int	main(int argc, char **argv, char **envp)
{
	int			is_here_doc;
	int			infile;
	t_cmd_info	cmd_info;

	if (argc && argv)
	{
		if (argc < 5)
			exit_print_model();
		is_here_doc = !ft_strncmp(argv[1], "here_doc", 8);
		cmd_info.argv = argv;
		cmd_info.is_hd = is_here_doc;
		if (is_here_doc)
			infile = do_here_doc(argv[2]);
		else
			infile = open(argv[1], O_RDONLY);
		if (infile == -1)
		{
			perror(argv[1]);
			exit(1);
		}
		dup2(infile, 0);
		close(infile);
		check_heredoc_and_run(argc, cmd_info, envp);
	}
	return (0);
}
