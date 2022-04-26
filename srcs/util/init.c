/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:53:49 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/26 17:28:55 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data, char **envp)
{
	ft_memset(data, 0, sizeof(t_data));
	data->envp = envp;
}

int	init(t_data *data, char **envp)
{
	init_data(data, envp);
	g_env_list = NULL;
	set_signal();
	if (!parse_env(envp))
		return (FALSE);
	return (TRUE);
}
