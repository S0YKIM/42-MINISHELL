/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/25 17:40:04 by sokim            ###   ########.fr       */
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
}

static int	parse_line(t_data *data, char *line)
{
	if (!tokenize(data, line))
		return (FALSE);
	if (!create_astree(data))
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
		if (!parse_line(data, line))
			exit(EXIT_FAILURE);
		if (!check_syntax_error(data))
			continue ;
		result = execute(data);
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
