# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tchian <tchian@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/21 19:42:25 by tchian            #+#    #+#              #
#    Updated: 2026/10/24 20:51:30 by tchian           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Archiver and Flags (The Linking Engine)
AR = ar
ARFLAGS = rcs

# Cleanup Command
RM = rm -f

# Source Files
SRCS =	get_next_line.c \
		get_next_line_utils.c \

# Object Files Translation
OBJS = $(SRCS:.c=.o)

# Default Rule
all: $(NAME)

# Linking Rule: Bundles .o files into libft.a
$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

# Implicit rule to compile .c files into .o files
%.o: %.c get_next_line.h get_next_line_bonus.h
		$(CC) $(CFLAGS) -c $< -o $@

# Cleanup Rules
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

# Protect rule names from matching actual files
.PHONY: all clean fclean re
