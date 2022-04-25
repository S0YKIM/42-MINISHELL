/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/26 01:06:06 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_loop(t_data *data, char *line)
{
	free(line);
	free_token_list(data);
	free_astree(data->astree);
	data->astree = NULL;
	free(data->pl_list);
	data->pl_list = NULL;
	data->pl_cnt = 0;
	data->curr_pl = 0;
	free(data->pids);
	data->pids = NULL;
}

static int	parse_and_execute(t_data *data, char *line)
{
	int	result;

	if (!tokenize(data, line))
		return (FALSE);
	if (!create_astree(data))
		return (FALSE);
	if (!check_syntax_error(data))
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
	if (!init(&data, envp))
		exit(EXIT_FAILURE);
	loop(&data);
	return (SUCCESS);
}
