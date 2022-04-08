#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*command;

	(void)argv;
	if (argc != 1)
		return (1);
	init_data(&data);
	if (!parse_env(envp, &data))
		exit(EXIT_FAILURE);
	while (1)
	{
		command = readline("microshell> ");
		add_history(command);
		printf("input: %s\n", command);
		free(command);
	}
	return (0);
}
