/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:57:46 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/25 16:56:35 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(pid_t pid)
{
	if (pid == ERROR)
	{
		printf("\b\b  \b\b\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		update_env("?", ft_strdup("1"));
	}
	else
	{
		printf("\n");
		update_env("?", ft_strdup("130"));
	}
}

static void	handle_sigquit(pid_t pid)
{
	if (pid == ERROR)
		printf("\b\b  \b\b");
	else
	{
		printf("Quit: 3\n");
		update_env("?", ft_strdup("131"));
	}
}

static void	handle_sigterm(pid_t pid)
{
	if (pid == ERROR)
	{
		printf("exit\n");
		update_env("?", ft_strdup("0"));
		exit (EXIT_SUCCESS);
	}
}

void	handle_signal(int signum)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (signum == SIGINT)
		handle_sigint(pid);
	else if (signum == SIGQUIT)
		handle_sigquit(pid);
	else
		handle_sigterm(pid);
}
