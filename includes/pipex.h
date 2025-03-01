/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:28:27 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/01 16:29:46 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>


void	run_processes(char **argv,  char **envp);

int		ft_isspace(char c);
char	**ft_get_command_path(char *argv, char **envp);
// int				ft_isnotdigit(char *str, int has_digit, int in_number);
void	free_ptr(void **p);
void	free_split(char **arr);
// void			free_list(t_stack *list);

#endif