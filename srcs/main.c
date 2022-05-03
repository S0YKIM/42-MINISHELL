/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/05/04 01:02:39 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	g_env_list = NULL;
	set_signal();
	if (!parse_env(envp))
		return (FALSE);
	return (TRUE);
}

static void	reset_loop(t_data *data, char *line)
{
	free(line);
	free_token_list(data);
	free_astree(data->astree);
	free(data->pl_list);
	free(data->pids);
	ft_memset(data, 0, sizeof(t_data));
}

static int	parse_and_execute(t_data *data, char *line)
{
	int	result;

	if (!tokenize(data, line))
		return (FALSE);
	if (data->token_list == NULL)
		return (ERROR);
	if (!create_astree(data))
		return (FALSE);
	if (!check_syntax_error(data, line))
		return (ERROR);
	result = execute(data);
	if (result == ERROR)
		return (ERROR);
	else if (!result)
		return (FALSE);
	return (TRUE);
}

static void	loop(t_data *data)
{
	char	*line;
	int		result;

	line = NULL;
	while (TRUE)
	{
		reset_loop(data, line);
		line = readline("microshell> ");
		if (!line)
		{
			printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		else if (!*line)
			continue ;
		add_history(line);
		result = parse_and_execute(data, line);
		if (result == ERROR)
			continue ;
		else if (!result)
			exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	print_art();
	if (!init(&data, envp))
		exit(EXIT_FAILURE);
	loop(&data);
	return (SUCCESS);
}
