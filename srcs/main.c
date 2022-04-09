#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argv;
	if (argc != 1)
		return (1);
	init_data(&data);
	if (!parse_env(envp, &data))
		exit(EXIT_FAILURE);
	while (1)
	{
		line = readline("microshell> ");
		if (!line)
			continue ;
		add_history(line);
		tokenize(&data, line);
		free(line);
		free_token_list(&data);
	}
	return (0);
}
