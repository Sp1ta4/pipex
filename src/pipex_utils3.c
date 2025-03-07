/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:45:06 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/07 17:23:12 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	wait_and_return_status(int *pid, int **chan, int len)
{
	int	i;
	int	last_status;
	int	status;
	int	exit_status;

	i = -1;
	last_status = 0;
	close_all_pipes(chan, len);
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

void	print_before_space(char *str)
{
	while (*str && !ft_isspace(*str))
	{
		write(2, str, 1);
		str++;
	}
	write(2, "\n", 1);
}
