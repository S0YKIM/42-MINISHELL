/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 19:52:52 by sokim             #+#    #+#             */
/*   Updated: 2022/04/19 15:04:59 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_code_reserved(char *code, char *argv)
{
	long long	num;

	num = ft_atol(code);
	printf("exit\n");
	if (num == 1)
		printf("microshell: exit: too many arguments\n");
	else if (num == 255)
		printf("microshell: exit: %s: numeric argument required\n", argv);
	update_env("?", ft_itoa(num));
	exit (num);
}

static int	change_num_into_range(long long raw)
{
	long long	num;
	int			ret;

	if (raw >= 0)
	{
		num = raw % 256;
		raw = raw / 256;
	}
	else
	{
		num = raw % 256;
		raw = raw / 256;
	}
	ret = (int)num;
	return (ret);
}

static void	exit_code_custom(char *code)
{
	long long	raw;
	int			num;

	printf("exit\n");
	update_env("?", code);
	raw = ft_atol(code);
	num = change_num_into_range(raw);
	update_env("?", ft_itoa(num));
	exit (num);
}

void	ft_exit(t_ast *ast, t_data *data)
{
	if (ast->argc == 1)
		exit_code_reserved("0", NULL);
	else if (ast->argc == 2)
	{
		if (!is_str_num(ast->argv[1]))
			exit_code_reserved("255", ast->argv[1]);
		if (!is_str_long_long(ast->argv[1]))
			exit_code_reserved("255", ast->argv[1]);
		exit_code_custom(ast->argv[1]);
	}
	else
		exit_code_reserved("1", NULL);
}
