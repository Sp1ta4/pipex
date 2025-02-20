#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:28:03 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/02/20 16:28:04 by ggevorgi         ###   ########.fr       */
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

int main()
{
	int p_child_to_parent[2];
	int p_parent_to_child[2];
	int	pid;
	int num;

	if (pipe(p_child_to_parent) == -1)
		return 1;
	if (pipe(p_parent_to_child) == -1)
		return 1;
	pid = fork();
	if (pid == -1)
		return 2;
	if (pid == 0)
	{
		int tmp;
		close(p_parent_to_child[1]);
		close(p_child_to_parent[0]);
		if (read(p_parent_to_child[0], &tmp, sizeof(tmp)) == -1)
			return 3;
		printf("Read from parent: %d\n", tmp);
		tmp *= 4;
		if(write(p_child_to_parent[1], &tmp, sizeof(tmp)) == -1)
			return 4;
	}
	else
	{
		close(p_child_to_parent[1]);
		close(p_parent_to_child[0]);
		num = rand() % 10;
		if (write(p_parent_to_child[1], &num, sizeof(num)) == -1)
			return 3;
		printf("Write from parent: %d\n", num);
		if(read(p_child_to_parent[0], &num, sizeof(num)) == -1)
			return 4;
		printf("Result: %d\n", num);
		wait(NULL);
	}


	return 0;
}
