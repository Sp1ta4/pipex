/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:28:27 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/06 14:29:37 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

void	run_processes(int argc, char **argv, char **envp);
int		wait_and_return_status(int *pid, int len);
void	print_before_space(char *str);
int		ft_isspace(char c);
char	**ft_get_command_path(char *argv, char **envp);
void	free_ptr(void **p);
void	free_split(char **arr);

#endif