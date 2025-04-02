# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dgeorgiy <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 16:44:12 by dgeorgiy          #+#    #+#              #
#    Updated: 2024/07/08 15:45:20 by dgeorgiy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
SRC = ft_atoi \
		ft_bzero \
		ft_calloc \
		ft_isalnum \
		ft_isalpha \
		ft_isdigit \
		ft_isascii \
		ft_isprint \
		ft_itoa \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_split \
		ft_strchr \
		ft_strdup \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strlen \
		ft_strmapi \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_tolower \
		ft_toupper

BSRC = ft_lstnew \
		ft_lstadd_front \
		ft_lstsize \
		ft_lstlast \
		ft_lstadd_back \
		ft_lstdelone \
		ft_lstclear \
		ft_lstiter \
		ft_lstmap

SRCS = $(addsuffix .c, $(SRC))
OBJS = $(addsuffix .o, $(SRC))

BSRCS = $(addsuffix .c, $(BSRC))
BOBJS = $(addsuffix .o, $(BSRC))

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@$(AR) $@ $^

all: $(NAME)

bonus: $(OBJS) $(BOBJS)
		$(AR) $(NAME) $^

clean: 
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean bonus re
