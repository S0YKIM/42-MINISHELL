/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/21 23:25:31 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*line;

	(void)argv;
	if (argc != 1)
		return (FAILURE);
	init_data(&data);
	g_env_list = NULL;
	set_signal();
	if (!parse_env(envp))
		exit(EXIT_FAILURE);
	while (TRUE)
	{
		line = readline("microshell> ");
		if (!line || !*line)
			continue ;
		add_history(line);
		if (!tokenize(&data, line))
			exit(EXIT_FAILURE);
		if (!create_astree(&data))
			exit(EXIT_FAILURE);
		execute_cmd(data.astree->right);
		if (!traverse_heredoc(data.astree))
			exit(EXIT_FAILURE);
		if (!traverse_fork(&data, data.astree))
			exit(EXIT_FAILURE);
		free(line);
		free_token_list(&data);
		free_astree(data.astree);
		free(data.pl_list);
		data.pl_cnt = 0;
		data.curr_pl = 0;
		data.astree = NULL;
	}
	return (SUCCESS);
}
