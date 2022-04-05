# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/05 19:07:22 by heehkim           #+#    #+#              #
#    Updated: 2022/04/05 19:15:03 by heehkim          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_strdup.c ft_strlen.c ft_strlcpy.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

.PHONY: clean
clean:
	rm -f $(OBJS)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean all
