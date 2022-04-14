NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR = srcs/
D_BUILTIN = builtins/
D_ENV = env/
D_PARSING = parsing/
D_UTIL = util/
SRC_LIST = main.c \
			$(D_BUILTIN)ft_env.c \
			$(D_BUILTIN)ft_pwd.c \
			$(D_BUILTIN)ft_export.c \
			$(D_BUILTIN)ft_cd.c \
			$(D_BUILTIN)ft_unset.c \
			$(D_BUILTIN)utils.c \
			$(D_ENV)get.c \
			$(D_ENV)update.c \
			$(D_ENV)remove.c \
			$(D_PARSING)env.c \
			$(D_PARSING)token.c \
			$(D_PARSING)trim.c \
			$(D_PARSING)expand.c \
			$(D_PARSING)ast.c \
			$(D_PARSING)ast_add.c \
			$(D_UTIL)init.c
SRCS = $(addprefix $(SRCDIR), $(SRC_LIST))
OBJS = $(SRCS:.c=.o)

LIBDIR = libft/
LIB_FLAGS = -L$(LIBDIR) -lft

MODE = EVAL
ifeq ($(MODE), EVAL)
	READLINE_DIR= ${HOME}/.brew/Cellar/readline/8.1.2
else ifeq ($(MODE), HEEHKIM)
	READLINE_DIR = /opt/homebrew/opt/readline
else ifeq ($(MODE), SOKIM)
	READLINE_DIR = /opt/homebrew/Cellar/readline/8.1.2
endif

INC_FLAGS = -I includes -I libft
LINK_FLAGS = -L${READLINE_DIR}/lib -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INC_FLAGS)

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@make -s -C $(LIBDIR)
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
	@make -s -C $(LIBDIR)
	$(CC) $(CFLAGS) -g -o $(NAME) $(SRCS) $(INC_FLAGS) $(LIB_FLAGS) $(LINK_FLAGS)

.PHONY: leak
leak:
	$(CC) $(CFLAGS) -g3 -fsanitize=address -o $(NAME) $(SRCS) $(INC_FLAGS)
