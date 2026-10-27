/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchian <tchian@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 22:46:52 by tchian            #+#    #+#             */
/*   Updated: 2026/10/25 20:37:51 by tchian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_to_remainder(int fd, t_stash *s)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (0);
	bytes_read = 1;
	while (!ft_strchr(s->data, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0 && !gnl_append(s, buffer, bytes_read))
			bytes_read = -1;
	}
	free(buffer);
	return (bytes_read >= 0);
}

static char	*extract_line(t_stash *s)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!s->len)
		return (NULL);
	i = 0;
	while (i < s->len && s->data[i] != '\n')
		i++;
	if (i < s->len)
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = s->data[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static void	clean_remainder(t_stash *s, size_t line_len)
{
	size_t	i;

	i = 0;
	while (line_len + i < s->len)
	{
		s->data[i] = s->data[line_len + i];
		i++;
	}
	s->len = i;
	s->data[i] = '\0';
}

static char	*gnl_reset(t_stash *s)
{
	free(s->data);
	s->data = NULL;
	s->len = 0;
	s->capacity = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_stash	s;
	char			*line;
	size_t			i;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (gnl_reset(&s));
	if (!read_to_remainder(fd, &s))
		return (gnl_reset(&s));
	line = extract_line(&s);
	if (!line)
		return (gnl_reset(&s));
	i = 0;
	while (line[i])
		i++;
	clean_remainder(&s, i);
	if (!s.len)
		gnl_reset(&s);
	return (line);
}