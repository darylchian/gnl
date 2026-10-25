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

static char	*read_to_remainder(int fd, char *remainder)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!strchr(remainder, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (free(remainder), NULL);
		}
		buffer[bytes_read] = '\0';
		if (!remainder)
			remainder = strdup("");
		temp = strjoin(remainder, buffer);
		free(remainder);
		remainder = temp;
	}
	free(buffer);
	return (remainder);
}

static char	*extract_line(char *remainder)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!remainder || !remainder[i])
		return (NULL);
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\n')
		line = malloc(sizeof(char) * (i + 2));
	else
		line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = -1;
	while (remainder[++i] && remainder[i] != '\n')
		line[i] = remainder[i];
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*clean_remainder(char *remainder)
{
	size_t	i;
	char	*new_remainder;

	i = 0;
	while (remainder[i] && remainder[i] != '\n')
		i++;
	if (!remainder[i])
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = strdup(remainder + i + 1);
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remainder = read_to_remainder(fd, remainder);
	if (!remainder)
		return (NULL);
	line = extract_line(remainder);
	remainder = clean_remainder(remainder);
	return (line);
}
