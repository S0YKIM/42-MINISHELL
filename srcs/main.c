/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:05:30 by sokim             #+#    #+#             */
/*   Updated: 2022/04/05 20:12:26 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	// char	*command;

	(void)argv;
	if (argc != 1)
		return (1);
	init_data(&data);
	if (!parse_env(envp, &data))
		exit(EXIT_FAILURE);
	// while (1)
	// {
	// 	command = readline("microshell> ");
	// 	add_history(command);
	// 	free(command);
	// 	//printf("input: %s\n", command);
	// }
	return (0);
}
