/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:49:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/03 12:53:39 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	do_first_command(char *file, char *cmd, char **envp, int chan[2])
{
	char	**commands;
	int		fd;

	printf("%s\n", file);
	fd = open(file, O_RDONLY);
	printf("%d\n", fd);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, 0);
	printf("%d, %d\n", chan[0], chan[1]);
	dup2(chan[1], 1);
	close(chan[0]);
	close(chan[1]);
	close(fd);
	commands = ft_get_command_path(cmd, envp);
	printf("%s, %s\n", commands[0], commands[1]);
	if (!commands)
	{
    	write(2, "command not found: ", 20);
		write(2, cmd, ft_strlen(cmd));
    	exit(127);
	}
	execve(commands[0], commands, envp);
	perror(commands[0]);
	free_split(commands);
	exit(127);
}

static void	do_command(char *cmd, char **envp, int inner_chan[2], int outter_chan[2])
{
	char	**commands;

	dup2(inner_chan[0], 0);
	dup2(outter_chan[1], 1);
	close(inner_chan[0]);
	close(inner_chan[1]);
	close(outter_chan[1]);
	commands = ft_get_command_path(cmd, envp);
	if (!commands)
	{
    	write(2, "command not found: ", 20);
		write(2, cmd, ft_strlen(cmd));
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
    	write(2, cmd, ft_strlen(cmd));
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
	int		channels[argc - 3][2];
	int		i;

	create_channels(channels, argc - 3);
	i = -1;
	printf("------> %d\n", argc);
	while (++i < argc - 2)
	{
		create_process(&pid[i]);
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				printf("======================> %s, %s\n", argv[0], argv[1]);
				do_first_command(argv[0], argv[1], envp, channels[0]);
			}
			else if (i == argc - 3)
				do_last_command(argv[i + 1], argv[i], envp, channels[i - 1]);		
			else
				do_command(argv[i + 1], envp, channels[i - 1], channels[i]);
		}
	}
	while (wait(NULL) > 0)
		;
}
