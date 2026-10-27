/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tchian <tchian@student.42singapore.sg>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/22 21:17:13 by tchian            #+#    #+#             */
/*   Updated: 2026/10/25 20:36:49 by tchian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h> //need for size_t
# include <unistd.h> //need for write
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_stash
{
	char	*data;
	size_t	len;
	size_t	capacity;
}	t_stash;
//Declaration of functionss

char	*get_next_line(int fd);
int		gnl_append(t_stash *s, char *buffer, size_t count);
char	*ft_strchr(const char *s, int c);

#endif
