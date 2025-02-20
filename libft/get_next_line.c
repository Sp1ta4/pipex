/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 16:12:22 by ggevorgi          #+#    #+#             */
/*   Updated: 2025/01/29 20:19:00 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	free_ptr(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

static int	check_buffer(char **buffer)
{
	if (!*buffer)
	{
		*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!*buffer)
			return (0);
		**buffer = '\0';
	}
	return (1);
}

ssize_t	ft_read_line(int fd, char **buffer)
{
	char	*temp;
	ssize_t	bytes_read;
	char	*new_buffer;

	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (-1);
	bytes_read = read(fd, temp, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		free(temp);
		if (bytes_read == -1)
			free_ptr(buffer);
		return (0);
	}
	temp[bytes_read] = '\0';
	new_buffer = ft_strjoin(*buffer, temp);
	free(temp);
	if (!new_buffer)
		return (-1);
	free_ptr(buffer);
	*buffer = new_buffer;
	return (bytes_read);
}

char	*extract_line(char **buffer, char *newline_pos)
{
	char	*line;
	char	*temp;

	line = ft_substr(*buffer, 0, newline_pos - *buffer + 1);
	if (!line)
		return (NULL);
	temp = ft_strdup(newline_pos + 1);
	if (!temp)
	{
		free(line);
		free_ptr(buffer);
		return (NULL);
	}
	free_ptr(buffer);
	*buffer = temp;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*newline_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!check_buffer(&buffer))
		return (NULL);
	while (1)
	{
		newline_pos = ft_strchr(buffer, '\n');
		if ((newline_pos))
			return (extract_line(&buffer, newline_pos));
		if (ft_read_line(fd, &buffer) <= 0)
			break ;
	}
	if (buffer && *buffer)
	{
		line = ft_strdup(buffer);
		free_ptr(&buffer);
		return (line);
	}
	free_ptr(&buffer);
	return (NULL);
}

// int main(int argc, char **argv)
// {
//     int fd;
//     char *line;

//     if (argc != 2)
//     {
//         printf("Usage: %s <filename>\n", argv[0]);
//         return (1);
//     }
//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0)
//     {
//         perror("Error opening file");
//         return (1);
//     }
//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//         free(line);
//     }
//     close(fd);
//     return (0);
// }
