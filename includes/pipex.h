/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:28:27 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/03/07 17:33:11 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

char	**ft_get_command_path(char *argv, char **envp);
void	run_processes(int count, char **args, char **env);
void	do_first_command(char *file, char *cmd, char **envp, int chan[2]);
void	do_command(char *cmd, char **envp, int i_chan[2], int o_chan[2]);
void	do_last_command(char *file, char *cmd, char **envp, int chan[2]);
void	create_channels(int *(**channels), int count);
void	create_process(pid_t *fid);
void	allocate_pid(pid_t *(*pid), int len);
void	free_resources(pid_t *pid, int **channels, int count);
void	print_before_space(char *str);
void	free_pointers_arr(int **arr);
void	free_ptr(void **p);
void	free_split(char **arr);
void	close_all_pipes(int **chan, int total_cmds);
int		wait_and_return_status(int *pid, int **chan, int len);
int		ft_isspace(char c);

#endif