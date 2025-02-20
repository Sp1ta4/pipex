/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggevorgi <sp1tak.gg@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 23:58:37 by ggevorgi          #+#    #+#             */
/*   Updated: 2024/10/30 14:03:11 by ggevorgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(const char *s, char c)
{
	int	i;
	int	is_inword;

	is_inword = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && !is_inword)
		{
			is_inword = 1;
			++i;
		}
		else if (*s == c)
			is_inword = 0;
		s++;
	}
	return (i);
}

void	ft_freesubstr(char **res, int index)
{
	int	i;

	i = -1;
	while (++i < index)
		free(res[i]);
	free(res);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		word_count;
	char	*start;
	char	**res;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	res = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	i = -1;
	while (++i < word_count)
	{
		while (*s == c)
			s++;
		start = (char *)s;
		while (*s && *s != c)
			s++;
		res[i] = ft_substr(start, 0, s - start);
		if (!res[i])
			return (ft_freesubstr(res, i), NULL);
	}
	res[i] = NULL;
	return (res);
}
