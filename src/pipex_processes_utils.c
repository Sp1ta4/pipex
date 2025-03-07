/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_processes_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:49:54 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/07 17:32:48 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	allocate_channels(int *(**channels), int len)
{
	int	i;

	i = 0;
	*channels = (int **)malloc(sizeof(int *) * (len + 1));
	if (!(*channels))
		exit(3);
	while (i <= len)
	{
		(*channels)[i] = NULL;
		i++;
	}
	i = 0;
	while (i < len)
	{
		(*channels)[i] = (int *)malloc(sizeof(int) * 2);
		if (!(*channels)[i])
		{
			free_pointers_arr(*channels);
			exit(3);
		}
		i++;
	}
}

static void	create_pipe(int *channel)
{
	if (pipe(channel) == -1)
	{
		perror("pipe");
		exit(1);
	}
}

void	create_channels(int *(**channels), int count)
{
	int	i;

	i = 0;
	allocate_channels(channels, count);
	while (i < count)
	{
		create_pipe((*channels)[i]);
		i++;
	}
}

void	allocate_pid(pid_t *(*pid), int len)
{
	*pid = (pid_t *)malloc(sizeof(pid_t) * len);
	if (!(*pid))
		exit(3);
}

void	free_resources(pid_t *pid, int **channels, int count)
{
	int	i;

	i = 0;
	if (pid)
	{
		free(pid);
		pid = NULL;
	}
	if (channels)
	{
		while (i < count)
		{
			if (channels[i])
			{
				free(channels[i]);
				channels[i] = NULL;
			}
			i++;
		}
		free(channels);
		channels = NULL;
	}
}
