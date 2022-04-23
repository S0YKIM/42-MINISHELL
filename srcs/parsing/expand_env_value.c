/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:52:23 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/23 17:59:29 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key_char(char c)
{
	if (!ft_isalpha(c) && c != '_')
		return (FALSE);
	return (TRUE);
}

static char	*expand_env_value_exception(char *i, char **key_end)
{
	char	*tmp;

	if (!**key_end)
		return (ft_strdup("$"));
	tmp = ft_strchr(*key_end, '\"');
	if (tmp)
		*key_end = tmp - 1;
	else
		(*key_end)--;
	return (ft_substr(i, 0, *key_end - i + 1));
}

static char	*join_dquote_str(char **key_end, char *value)
{
	char	*str_end;
	char	*tail;
	char	*tmp;

	str_end = ft_strchr(*key_end + 1, '\"') - 1;
	if (str_end == *key_end)
		return (value);
	tail = ft_substr(*key_end + 1, 0, str_end - *key_end);
	if (!tail)
		return (NULL);
	tmp = value;
	value = ft_strjoin(value, tail);
	free(tmp);
	free(tail);
	*key_end = str_end;
	return (value);
}

char	*expand_env_value(char *i, char **key_end, int is_dquote)
{
	char	*key_start;
	char	*key;
	char	*value;

	key_start = i + 1;
	*key_end = key_start;
	if (**key_end != '?' && !is_valid_key_char(**key_end))
		return (expand_env_value_exception(i, key_end));
	while (**key_end)
	{
		if (**key_end == '?')
			break ;
		if (!*(*key_end + 1) || !is_valid_key_char(*(*key_end + 1)))
			break ;
		(*key_end)++;
	}
	key = ft_substr(key_start, 0, *key_end - key_start + 1);
	if (!key)
		return (NULL);
	value = get_env_value(key);
	free(key);
	if (is_dquote)
		return (join_dquote_str(key_end, value));
	return (value);
}
