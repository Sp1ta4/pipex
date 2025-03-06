/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:49:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/06 14:31:54 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_first_command(char *file, char *cmd, char **envp, int chan[2])
{
	char	**commands;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, 0);
	dup2(chan[1], 1);
	close(chan[0]);
	close(chan[1]);
	close(fd);
	commands = ft_get_command_path(cmd, envp);
	if (!commands)
	{
		write(2, "command not found: ", 20);
		print_before_space(cmd);
		exit(127);
	}
	execve(commands[0], commands, envp);
	perror(commands[0]);
	free_split(commands);
	exit(127);
}

static void	do_command(char *cmd, char **envp, int i_chan[2], int o_chan[2])
{
	char	**commands;

	dup2(i_chan[0], 0);
	dup2(o_chan[1], 1);
	close(i_chan[0]);
	close(i_chan[1]);
	close(o_chan[1]);
	commands = ft_get_command_path(cmd, envp);
	if (!commands)
	{
		write(2, "command not found: ", 20);
		print_before_space(cmd);
		write(2, "\n", 1);
		exit(127);
	}
	execve(commands[0], commands, envp);
	perror(commands[0]);
	exit(127);
}

static void	do_last_command(char *file, char *cmd, char **envp, int chan[2])
{
	int		fd;
	char	**commands;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, 1);
	dup2(chan[0], 0);
	close(chan[0]);
	close(chan[1]);
	close(fd);
	commands = ft_get_command_path(cmd, envp);
	if (!commands)
	{
		write(2, "command not found: ", 20);
		print_before_space(cmd);
		write(2, "\n", 1);
		exit(127);
	}
	execve(commands[0], commands, envp);
	perror(commands[0]);
	exit(127);
}

static void	create_pipe(int (*channel)[2])
{
	if (pipe(*channel) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

static void	create_channels(int channels[][2], int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		create_pipe(&channels[i]);
	}
}

static void	create_process(pid_t *fid)
{
	*fid = fork();
	if (*fid == -1)
	{
		perror("fork");
		exit(1);
	}
}
void	run_processes(int argc, char **argv, char **envp)
{
	pid_t	pid[argc - 2];
	int		chan[argc - 3][2];
	int		i;

	// allocate_pid(&pid, argc - 2);            // Выделение памяти для pid
	// allocate_channels(&chan, argc - 3);      // Выделение памяти для каналов
	create_channels(chan, argc - 3);         // Создание каналов
	i = -1;
	while (++i < argc - 2)
	{
		create_process(&pid[i]);  // Создание процесса
		if (pid[i] == 0) // В дочернем процессе
		{
			if (i == 0)
				do_first_command(argv[0], argv[1], envp, chan[0]);
			else if (i == argc - 3)
				do_last_command(argv[i + 2], argv[i + 1], envp, chan[i - 1]);
			else
				do_command(argv[i + 1], envp, chan[i - 1], chan[i]);
		}
		else
			close(chan[i][1]); // Закрытие записи в канале родительским процессом
	}
	// free_resources(pid, chan, argc - 3);
	exit(wait_and_return_status(pid, argc - 2));
}

