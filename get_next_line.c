/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchian <tchian@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/24 22:46:52 by tchian            #+#    #+#             */
/*   Updated: 2026/10/25 17:03:51 by tchian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	read_strj(int fd, char *buffer, char *stash)
{
	char	*tmp;
	ssize_t	n;

	n = read(fd, buffer, BUFFER_SIZE);
	if (n < 0)
		return (-1);
	if (n == 0)
		return (0);
	buffer[n] = '\0';
	tmp = ft_strjoin(stash, buffer);
	if (!tmp)
	{
		return (-1);
	}
	free(stash);
	stash = tmp;
	return (1);
}

static char	*fill_stash(int fd, char *stash)
{
	char	*buffer;
	int		status;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	status = 1;
	while (status > 0 && ft_strchr(stash, '\n') == NULL)
		status = read_strj(fd, buffer, &stash);
	free(buffer);
	if (status < 0)
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

static char	*make_line(char *stash)
{
	char	*newl;
	char	*line;
	char	temp;

	newl = ft_strchr(stash, '\n');
	if (!newl)
		return (ft_strdup(stash));
	temp = newl[1];
	newl[1] = '\0';
	line = ft_strdup(stash);
	newl[1] = temp;
	return (line);
}

static char	*leftover(char *stash)
{
	char	*newl;

	newl = ft_strchr(stash, '\n');
	if (!newl || !*(newl +1))
		return (NULL);
	return (ft_strdup(newl + 1));
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
	line = make_line(stash);
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
