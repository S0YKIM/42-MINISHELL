/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 19:52:52 by sokim             #+#    #+#             */
/*   Updated: 2022/04/15 21:27:24 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_code_reserved(t_data *data, char *code, char *argv)
{
	long long	num;

	num = ft_atol(code);
	printf("exit\n");
	if (num == 1)
		printf("exit: too many arguments\n");
	else if (num == 255)
		printf("exit: %s: numeric argument required\n", argv);
	update_env(data, "?", code);
	exit (num);
}

static void	exit_code_custom(t_data *data, char *code)
{
	printf("exit\n");
	update_env(data, "?", code);
	exit (ft_atol(code));
}

void	ft_exit(t_ast *ast, t_data *data)
{
	if (ast->argc == 1)
		exit_code_reserved(data, "0", NULL);
	else if (ast->argc == 2)
	{
		if (!is_str_num(ast->argv[1]))
			exit_code_reserved(data, "255", ast->argv[1]);
		if (!is_str_long_long(ast->argv[1]))
			exit_code_reserved(data, "255", ast->argv[1]);
		exit_code_custom(data, ast->argv[1]);
	}
	else
		exit_code_reserved(data, "1", NULL);
}
