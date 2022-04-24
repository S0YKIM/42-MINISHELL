/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/24 16:19:38 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_line(t_data *data, char *line)
{
	if (!tokenize(data, line))
		return (FALSE);
	if (!create_astree(data))
		return (FALSE);
	return (TRUE);
}

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

static void	loop(t_data *data)
{
	char	*line;

	line = NULL;
	while (TRUE)
	{
		reset_loop(data, line);
		line = readline("microshell> ");
		if (!line || !*line)
			continue ;
		add_history(line);
		if (!parse_line(data, line))
			exit(EXIT_FAILURE);
		if (!check_syntax_error(data))
			continue ;
		if (!execute(data))
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
