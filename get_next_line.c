/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchian <tchian@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 22:46:52 by tchian            #+#    #+#             */
/*   Updated: 2026/10/25 15:59:09 by tchian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_once(int fd, char **stash, char *bufer)
{
	ssize_t	n;
	char	*temp;

	n = read(fd, bufer, BUFFER_SIZE);
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	buffer[n] = '\0';
	tmp = ft_strjoin(*stash, buffer);
	free(*stash);
	*stash = tmp;
	if (!tmp)
		return (-1);
	return (1);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	int		status;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	status = 1;
	while (status > 0 && !ft_strchr(stash, '\n'))
	{
		status = read_once(fd, &stash, buffer);
	}
	free(buffer);
	if (status < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

static size_t	line_len(char *stash)
{
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (i);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || !*stash)
		return (NULL);
	len = line_len(stash);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*left;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = fill_stash(fd, stash);
	if (!stash || !*stash)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	left = leftover(stash);
	free(stash);
	stash = left;
	return (line);
}
