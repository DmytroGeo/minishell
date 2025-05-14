# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/12 12:03:28 by dgeorgiy          #+#    #+#              #
#    Updated: 2025/05/13 18:40:38 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = liblists.a
CC = cc
AR = ar rcs
# 'ar' is like 'cc' but for compiling static libraries.
# "Create (c) the archive if it doesn't exist, replace (r) existing object files, and generate an index (s)."
FLAGS = -Wall -Wextra -Werror
SOURCES = ft_array_free.c \
			ft_array_len.c \
			ft_find_node.c \
			ft_free.c \
			ft_intarr_free.c \
			ft_lstadd_front.c \
			ft_lstclear.c \
			ft_lstnew.c \
			ft_lstsize.c \
			ft_memcpy.c \
			ft_perror.c \
			ft_printf.c \
			ft_putchar_fd.c \
			ft_putchex_fd.c \
			ft_puthex_fd.c \
			ft_putnbr_fd.c \
			ft_putptr_fd.c \
			ft_putstr_fd.c \
			ft_putuns_fd.c \
			ft_split.c \
			ft_strcpy.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strncmp.c \
			ft_strnstr.c 

OBJECTS = $(SOURCES:.c=.o)

%.o : %.c $(HEADERS)
		@$(CC) $(FLAGS) -c $< -o $@

# You don’t need -o when using ar! That flag is used by cc to specify an output file, but ar works differently. 
# The correct way to archive object files looks like this:
# $(AR) expands to ar rcs, meaning "create or update the archive".
# $(NAME) (which is libft.a) is the output archive.
# $(OBJECTS) are the input files (the compiled .o files).

$(NAME): $(OBJECTS)
		@$(AR) $(NAME) $(OBJECTS)

# I could instead write 'libft.a: $(OBJECTS)
# 	$(AR) libft.a $(OBJECTS)' but using variables is better.

all: $(NAME)

clean: 
		@rm -f $(OBJECTS)

fclean:	clean
		@rm -f $(NAME)
		
re: fclean all

.PHONY: all clean fclean re