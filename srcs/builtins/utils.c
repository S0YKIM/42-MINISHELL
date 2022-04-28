/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokim <sokim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 23:38:55 by sokim             #+#    #+#             */
/*   Updated: 2022/04/18 14:47:18 by sokim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_str_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static int	is_space(int c)
{
	if (c == ' ' || (9 <= c && c <= 13))
		return (1);
	return (0);
}

int	is_str_long_long(char *str)
{
	unsigned long long	num;
	int					sign;

	num = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		if (sign == 1 && num > LONG_MAX)
			return (FALSE);
		else if (sign == -1 && num - 1 > LONG_MAX)
			return (FALSE);
		str++;
	}
	return (TRUE);
}

int	is_valid_key_name(char *key)
{
	if (!key || !key[0])
		return (FALSE);
	if (ft_isdigit(key[0]))
		return (FALSE);
	if (ft_strchr(key, '?'))
		return (FALSE);
	return (TRUE);
}
