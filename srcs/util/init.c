/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:53:49 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/26 22:04:42 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_data(t_data *data)
{
	ft_memset(data, 0, sizeof(t_data));
}

int	init(t_data *data, char **envp)
{
	init_data(data);
	g_env_list = NULL;
	set_signal();
	if (!parse_env(envp))
		return (FALSE);
	return (TRUE);
}
