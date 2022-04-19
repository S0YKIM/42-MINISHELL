/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 16:41:06 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/19 23:04:25 by heehkim          ###   ########.fr       */
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
		if (!line)
			continue ;
		add_history(line);
		if (!tokenize(&data, line))
			exit(EXIT_FAILURE);
		if (!create_astree(&data))
			exit(EXIT_FAILURE);
		if (!ft_strcmp(data.astree->right->argv[0], "cd"))
			ft_cd(data.astree->right);
		else if (!ft_strcmp(data.astree->right->argv[0], "echo"))
			ft_echo(data.astree->right);
		else if (!ft_strcmp(data.astree->right->argv[0], "env"))
			ft_env(data.astree->right);
		else if (!ft_strcmp(data.astree->right->argv[0], "exit"))
			ft_exit(data.astree->right);
		else if (!ft_strcmp(data.astree->right->argv[0], "export"))
			ft_export(data.astree->right);
		else if (!ft_strcmp(data.astree->right->argv[0], "pwd"))
			ft_pwd();
		else if (!ft_strcmp(data.astree->right->argv[0], "unset"))
			ft_unset(data.astree->right);
		if (!traverse_heredoc(data.astree))
			exit(EXIT_FAILURE);
		if (!fork_process(&data))
			exit(EXIT_FAILURE);
		free(line);
		free_token_list(&data);
		free_astree(data.astree);
		data.astree = NULL;
	}
	return (SUCCESS);
}
