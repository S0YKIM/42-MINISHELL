#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <sys/errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "struct.h"

# define TRUE		1
# define FALSE		0

void	init_data(t_data *data);

int		parse_env(char **envp, t_data *data);

#endif
