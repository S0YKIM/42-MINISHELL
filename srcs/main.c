/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 20:05:30 by sokim             #+#    #+#             */
/*   Updated: 2022/04/04 21:29:23 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*command;

	(void)argv;
	//(void)env;
	if (argc != 1)
		return (1);
	for (int i = 0; i < 3; i++)
		{
			printf("%i번째 : %s\n", i, env[i]);
		}
	while (1)
	{
		command = readline("microshell> ");
		add_history(command);
		free(command);
		//printf("input: %s\n", command);
	}
	return (0);
}