/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchian <tchian@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 21:17:13 by tchian            #+#    #+#             */
/*   Updated: 2026/10/25 20:39:28 by tchian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

static size_t	gnl_capacity(t_stash *s, size_t count)
{
	size_t	capacity;

	if (count > (size_t)-1 - s->len - 1)
		return (0);
	capacity = s->capacity;
	if (!capacity)
		capacity = 64;
	while (capacity < s->len + count + 1)
	{
		if (capacity > (size_t) - 1 / 2)
			return (0);
		capacity *= 2;
	}
	return (capacity);
}

static void	gnl_copy(char *dst, char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

static int	gnl_grow(t_stash *s, size_t count)
{
	size_t	capacity;
	char	*new_data;

	if (count <= s->capacity
		&& s->len < s->capacity - count)
		return (1);
	capacity = gnl_capacity(s, count);
	if (!capacity)
		return (0);
	new_data = malloc(capacity);
	if (!new_data)  
		return (0);
	if (s->data)
		gnl_copy(new_data, s->data, s->len);
	else
		new_data[0] = '\0';
	free(s->data);
	s->data = new_data;
	s->capacity = capacity;
	return (1);
}

int	gnl_append(t_stash *s, char *buffer, size_t count)
{
	size_t	i;

	if (!gnl_grow(s, count))
		return (0);
	i = 0;
	while (i < count)
	{
		s->data[s->len + i] = buffer[i];
		i++;
	}
	s->len += count;
	s->data[s->len] = '\0';
	return (1);
}