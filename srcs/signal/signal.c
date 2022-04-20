/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:00:53 by sokim             #+#    #+#             */
/*   Updated: 2022/04/20 16:38:49 by sokim            ###   ########.fr       */
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

static void	handle_signal(int signum)
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

void	set_signal(void)
{
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTERM, handle_signal);
}
