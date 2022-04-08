CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a

SRCS = ft_strdup.c	\
		ft_strlen.c	\
		ft_strlcpy.c	\
		ft_memset.c
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
