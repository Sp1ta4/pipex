/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 19:33:53 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/09 18:39:59 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_here_doc_file(void)
{
	int	fd;

	fd = open("heredoc_file", O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	return (fd);
}

int	do_here_doc(char *lim)
{
	int		fd;
	char	*line;

	fd = open("heredoc_file", O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	line = get_next_line(STDIN_FILENO);
	while (line)
	{
		if (strncmp(line, lim, strlen(lim)) == 0 && line[strlen(lim)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
	close(fd);
	return (open_here_doc_file());
}

void	check_heredoc_and_run(int ac, t_cmd_info cmd_info, char **envp)
{
	if (cmd_info.is_hd)
	{
		cmd_info.argv += 3;
		run_processes(ac - 4, cmd_info, envp);
	}
	else
	{
		cmd_info.argv += 2;
		run_processes(ac - 3, cmd_info, envp);
	}
}
