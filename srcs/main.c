/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/18 22:17:37 by heehkim          ###   ########.fr       */
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
	if (!parse_env(envp, &data))
		exit(EXIT_FAILURE);
	while (TRUE)
	{
		line = readline("microshell> ");
		if (!line)
			continue ;
		add_history(line);
		if (!tokenize(&data, line))
			exit(EXIT_FAILURE);
		if (!create_astree(&data))
			exit(EXIT_FAILURE);
		if (!traverse_heredoc(data.astree))
			exit(EXIT_FAILURE);
		free(line);
		free_token_list(&data);
		free_astree(data.astree);
		data.astree = NULL;
	}
	return (SUCCESS);
}
