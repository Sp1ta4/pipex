/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_main_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:34:46 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/09 18:38:25 by ggevorgi         ###   ########.fr       */
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

void	run_processes(int cmd_count, t_cmd_info cmd_info, char **envp)
{
	pid_t	*pid;
	int		**chan;
	int		status;
	int		i;

	allocate_pid(&pid, cmd_count);
	create_channels(&chan, cmd_count - 1);
	i = -1;
	while (++i < cmd_count)
	{
		create_process(&pid[i]);
		if (pid[i] == 0)
		{
			close_unused_pipes(chan, i, cmd_count);
			if (i == 0)
				do_first_command(cmd_info.argv[0], envp, chan[0]);
			else if (i == cmd_count - 1)
				do_last_command(cmd_info, i, envp, chan[i - 1]);
			else
				do_command(cmd_info.argv[i], envp, chan[i - 1], chan[i]);
		}
	}
	status = wait_and_return_status(pid, chan, cmd_count);
	free_resources(pid, chan, cmd_count - 1);
	exit(status);
}
