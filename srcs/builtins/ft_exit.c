/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 19:52:52 by sokim             #+#    #+#             */
/*   Updated: 2022/04/24 21:32:15 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_too_many_arg(void)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putendl_fd(": exit: too many arguments", STDERR_FILENO);
}

static void	print_numeric_arg_required(char *argv)
{
	ft_putstr_fd(SHELL_NAME, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(argv, STDERR_FILENO);
	ft_putendl_fd("numeric argument required", STDERR_FILENO);
}

static void	exit_code_reserved(char *code, char *argv, int cnt)
{
	long long	num;

	num = ft_atol(code);
	if (cnt == 1)
		printf("exit\n");
	if (num == 1)
		print_too_many_arg();
	else if (num == 255)
		print_numeric_arg_required(argv);
	exit(num);
}

static void	exit_code_custom(char *code, int cnt)
{
	long long	num;

	if (cnt == 1)
		printf("exit\n");
	num = ft_atol(code);
	exit(num);
}

void	ft_exit(t_ast *ast, t_data *data)
{
	if (ast->argc == 1)
		exit_code_reserved("0", NULL, data->pl_cnt);
	else if (ast->argc == 2)
	{
		if (!is_str_num(ast->argv[1]))
			exit_code_reserved("255", ast->argv[1], data->pl_cnt);
		if (!is_str_long_long(ast->argv[1]))
			exit_code_reserved("255", ast->argv[1], data->pl_cnt);
		exit_code_custom(ast->argv[1], data->pl_cnt);
	}
	else
		exit_code_reserved("1", NULL, data->pl_cnt);
}
