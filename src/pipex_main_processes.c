/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:34:46 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/07 17:09:49 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_unused_pipes(int **chan, int i, int total_cmds)
{
	int	j;

	j = -1;
	while (++j < total_cmds - 1)
	{
		if (j != i - 1)
			close(chan[j][0]);
		if (j != i)
			close(chan[j][1]);
	}
}

void	close_all_pipes(int **chan, int total_cmds)
{
	int	i;

	i = -1;
	while (++i < total_cmds - 1)
	{
		close(chan[i][0]);
		close(chan[i][1]);
	}
}

void	run_processes(int argc, char **argv, char **envp)
{
	pid_t	*pid;
	int		**chan;
	int		status;
	int		i;

	allocate_pid(&pid, argc - 2);
	create_channels(&chan, argc - 3);
	i = -1;
	while (++i < argc - 2)
	{
		create_process(&pid[i]);
		if (pid[i] == 0)
		{
			close_unused_pipes(chan, i, argc - 2);
			if (i == 0)
				do_first_command(argv[0], argv[1], envp, chan[0]);
			else if (i == argc - 3)
				do_last_command(argv[i + 2], argv[i + 1], envp, chan[i - 1]);
			else
				do_command(argv[i + 1], envp, chan[i - 1], chan[i]);
		}
	}
	status = wait_and_return_status(pid, chan, argc - 2);
	free_resources(pid, chan, argc - 3);
	exit(status);
}
