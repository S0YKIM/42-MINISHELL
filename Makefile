# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 20:05:45 by sokim             #+#    #+#              #
#    Updated: 2022/04/04 21:04:31 by sokim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS = srcs/main.c
OBJS = $(SRCS:.c=.o)

READLINE_DIR = ${HOME}/.brew/Cellar/readline/8.1.2
INC_FLAGS = -I includes
LINK_FLAGS = -L${READLINE_DIR}/lib -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LINK_FLAGS)

bonus : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

test :
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(INC_FLAGS)

leak :
	$(CC) $(CFLAGS) -g3 -fsanitize=address -o $(NAME) $(SRCS) $(INC_FLAGS)

.PHONY : all clean fclean re bonus