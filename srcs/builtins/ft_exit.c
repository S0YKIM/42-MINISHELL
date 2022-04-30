/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 19:52:52 by sokim             #+#    #+#             */
/*   Updated: 2022/04/30 21:30:12 by sokim            ###   ########.fr       */
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
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

static long long	exit_code_reserved(char *code, char *argv)
{
	long long	num;

	num = ft_atol(code);
	if (num == 0)
	{
		printf("exit\n");
		exit(num);
	}
	if (num == 1)
		print_too_many_arg();
	else if (num == 255)
		print_numeric_arg_required(argv);
	return (num);
}

static void	exit_code_custom(char *code)
{
	long long	num;

	printf("exit\n");
	num = ft_atol(code);
	exit(num);
}

int	ft_exit(t_ast *ast)
{
	if (ast->argc == 1)
		return (exit_code_reserved("0", NULL));
	else if (ast->argc == 2)
	{
		if (!is_str_num(ast->argv[1]) \
			|| !is_str_long_long(ast->argv[1]))
			return (exit_code_reserved("255", ast->argv[1]));
		else
			exit_code_custom(ast->argv[1]);
	}
	else
		return (exit_code_reserved("1", NULL));
	return (0);
}
