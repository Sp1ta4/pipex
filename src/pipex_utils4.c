/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 17:29:26 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/09 18:39:36 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	do_first_command(char *cmd, char **envp, int chan[2])
{
	char	**commands;

	dup2(chan[1], 1);
	close(chan[0]);
	close(chan[1]);
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

static int	open_file_dup_stdo(char *file, int is_heredoc)
{
	int	fd;

	if (is_heredoc)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, 1);
	return (fd);
}

void	do_last_command(t_cmd_info cmd_info, int i, char **envp, int chan[2])
{
	int		fd;
	char	**commands;

	fd = open_file_dup_stdo(cmd_info.argv[i + 1], cmd_info.is_hd);
	dup2(chan[0], 0);
	close(chan[0]);
	close(chan[1]);
	close(fd);
	commands = ft_get_command_path(cmd_info.argv[i], envp);
	if (!commands)
	{
		write(2, "command not found: ", 20);
		print_before_space(cmd_info.argv[i]);
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
