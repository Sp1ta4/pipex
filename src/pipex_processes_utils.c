/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:49:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/01 17:03:20 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "errno.h"
#include "string.h"
static void	do_first_command(char *infile, char *command, char **envp, int channel[2])
{
	char	**commands;
	char	fd;
	
	fd = open(infile, O_RDONLY);
	printf("-----------> %d\n", fd);
	if (fd == -1)
	{
		printf("%s\n", strerror(errno));
		exit(1);
	}
	dup2(fd, 0);
	dup2(channel[1], 1);
	close(channel[0]);
	close(channel[1]);
	close(fd);
	commands = ft_get_command_path(command, envp);
	if (!commands)
	{
		close(channel[0]);
		perror("command not found");
		exit(1);
	}
	execve(commands[0], commands, envp);
	perror("execve");
	free_split(commands);
	exit(127);
}


static void	do_seccond_command(char *outfile, char *command, char **envp, int channel[2])
{
	int		fd;
	char	**commands;
	
	fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit(1);
	dup2(fd, 1);
	dup2(channel[0], 0);
	close(channel[0]);
	close(channel[1]);
	close(fd);
	commands = ft_get_command_path(command, envp);
	if (!commands)
	{
		close(channel[0]);
		perror("command not found");
		exit(1);
	}
	execve(commands[0], commands, envp);
	perror("execve");
}

static void create_pipe(int (*channel)[2])
{
    if (pipe(*channel) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

static void create_process(pid_t *fid)
{
	*fid = fork();
	if (*fid == -1)
	{
		perror("fork");
		exit(1);
	}
}


void	run_processes(char **argv,  char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	int		channel[2];
	
	create_pipe(&channel);
	create_process(&pid1);
	if (pid1 == 0)
		do_first_command(argv[1], argv[2], envp, channel);
	create_process(&pid2);
	if (pid2 == 0)
		do_seccond_command(argv[4], argv[3], envp, channel);
	close(channel[0]);
	close(channel[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	
}
