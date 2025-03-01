/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:56:56 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/01 16:24:33 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char *ft_getenv(char **envp)
{
	int	i;
	
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*take_correct_path(char *command, char *path)
{
	char	**paths;
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	while (paths[i] != NULL)
	{
		tmp = ft_strjoin(paths[i], "/");
		tmp2 = ft_strjoin(tmp, command);
		free(tmp);
		if (access(tmp2, F_OK) != -1)
		{
			free_split(paths);
			return (tmp2);
		}
		free(tmp2);
		i++;
	}
	free_split(paths);
	return (NULL);
}

static int	ft_getcommands(char *arg, char ***commands)
{
	char	**splitted;

	splitted = ft_split(arg, ' ');
	if (!splitted)
		return (0);	
	(*commands)[0] = ft_strdup(splitted[0]);
	if (splitted[1])
		(*commands)[1] =  ft_strdup(splitted[1]);
	else
		(*commands)[1] = NULL;	
	if (!(*commands)[0] || (splitted[1] && !(*commands)[1]))
	{
		free((*commands)[0]);
		free((*commands)[1]);
		free_split(splitted);
		return (0);
	}
	free_split(splitted);
	return (1);
}

char **ft_get_command_path(char *argv, char **envp)
{
	char	*env;
	char	**commands;
	
	env = ft_getenv(envp);
	if (!env)
		return (NULL);
	commands = malloc(sizeof(char *) * 3);
	if (!commands)
		return (NULL);
	if (!ft_getcommands(argv, &commands))
	{
		free(commands);
		return (NULL);
	}
	commands[0] = take_correct_path(commands[0], env);
	if (!commands[0])
	{
		free(commands[1]);
		free(commands);
		return (NULL);
	}
	commands[2] = NULL;
	return (commands);
}
