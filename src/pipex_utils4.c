/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:29:26 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/07 18:59:54 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_first_command(char *file, char *cmd, char **envp, int chan[2])
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

void	do_command(char *cmd, char **envp, int i_chan[2], int o_chan[2])
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
		exit(127);
	}
	execve(commands[0], commands, envp);
	perror(commands[0]);
	exit(127);
}

void	do_last_command(char *file, char *cmd, char **envp, int chan[2])
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
		exit(127);
	}
	execve(commands[0], commands, envp);
	perror(commands[0]);
	exit(127);
}

void	create_process(pid_t *fid)
{
	*fid = fork();
	if (*fid == -1)
	{
		perror("fork");
		exit(1);
	}
}
