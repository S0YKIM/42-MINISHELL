/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 14:15:50 by sokim             #+#    #+#             */
/*   Updated: 2022/05/01 16:49:45 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_n_option(char **argv, int *i)
{
	int	flag;
	int	j;

	flag = FALSE;
	*i = 1;
	while (argv[*i])
	{
		if (argv[*i][0] == '-' && argv[*i][1] == 'n')
		{
			j = 2;
			while (argv[*i][j])
			{
				if (argv[*i][j] != 'n')
					return (flag);
				j++;
			}
			flag = TRUE;
		}
		else
			return (flag);
		(*i)++;
	}
	return (flag);
}

int	ft_echo(t_ast *ast)
{
	int		i;
	int		flag;
	char	*tmp;

	flag = check_n_option(ast->argv, &i);
	while (ast->argv[i])
	{
		if (is_there_tilde(ast->argv[i]))
		{
			tmp = join_home_directory(ast->argv[i]);
			printf("%s", tmp);
		}
		else
			printf("%s", ast->argv[i]);
		if (ast->argv[++i])
			printf(" ");
	}
	if (flag == FALSE)
		printf("\n");
	return (SUCCESS);
}
