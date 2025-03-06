/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 13:48:34 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/06 14:12:07 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_isspace(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

void	free_ptr(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_list(t_stack *list)
{
	t_stack	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

int	wait_and_return_status(int *pid, int len)
{
	int	i;
	int	last_status;
	int	status;
	int	exit_status;

	i = -1;
	last_status = 0;
	while (++i < len)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			exit_status = WEXITSTATUS(status);
			if (exit_status != 0)
				last_status = exit_status;
		}
		else if (WIFSIGNALED(status))
		{
			last_status = 128 + WTERMSIG(status);
		}
	}
	return (last_status);
}
