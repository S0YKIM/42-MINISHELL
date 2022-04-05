NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = srcs/
SRCS = $(addprefix $(SRCDIR), main.c init.c env.c)
OBJS = $(SRCS:.c=.o)

LIBDIR = libft/
LIB_FLAGS = -L$(LIBDIR) -lft

# heeehkim local path
READLINE_DIR = /opt/homebrew/opt/readline
# READLINE_DIR = ${HOME}/.brew/Cellar/readline/8.1.2
INC_FLAGS = -I includes -I libft
LINK_FLAGS = -L${READLINE_DIR}/lib -lreadline

%.o: %.c
	@make -s -C $(LIBDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIB_FLAGS) $(LINK_FLAGS)

.PHONY: clean
clean:
	@make clean -s -C $(LIBDIR)
	rm -rf $(OBJS)

.PHONY: fclean
fclean: clean
	@make fclean -s -C $(LIBDIR)
	rm -rf $(NAME)

.PHONY: re
re: fclean all

.PHONY: debug
debug:
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(INC_FLAGS)

.PHONY: leak
leak:
	$(CC) $(CFLAGS) -g3 -fsanitize=address -o $(NAME) $(SRCS) $(INC_FLAGS)
