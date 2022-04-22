/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 19:17:20 by sokim             #+#    #+#             */
/*   Updated: 2022/04/22 22:29:01 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_invalid_identifier(char *cmd, char *argv)
{
	printf("%s: %s: `%s': ", SHELL_NAME, cmd, argv);
	printf("not a valid identifier\n");
}

void	print_full_no_such_file(char *cmd, char *argv)
{
	printf("%s: %s: %s: ", SHELL_NAME, cmd, argv);
	printf("No such file or directory\n");
}

void	print_no_such_file(char *cmd, char *argv)
{
	printf("%s: %s: ", cmd, argv);
	printf("No such file or directory\n");
}

void	print_not_set(char *cmd, char *argv)
{
	printf("%s: %s: %s not set\n", SHELL_NAME, cmd, argv);
}
