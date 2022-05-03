/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 17:52:23 by heehkim           #+#    #+#             */
/*   Updated: 2022/05/03 20:06:13 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key_char(char c)
{
	if (!ft_isdigit(c) && !ft_isalpha(c) && c != '_')
		return (FALSE);
	return (TRUE);
}

static char	*expand_env_value_exception(char *i, char **key_end, int is_dquote)
{
	char	*tmp;

	if (!**key_end || ft_strchr(" $", **key_end))
	{
		(*key_end)--;
		return (ft_strdup("$"));
	}
	if (!is_dquote && ft_strchr("\"\'", **key_end))
	{
		(*key_end)--;
		return (ft_strdup(""));
	}
	if (!ft_strchr("\"\'$", **key_end) && !ft_isalpha(**key_end))
		return (ft_strdup(""));
	tmp = ft_strchr(*key_end, '\"');
	if (tmp && is_dquote)
		*key_end = tmp - 1;
	else
		(*key_end)--;
	return (ft_substr(i, 0, *key_end - i + 1));
}

char	*expand_env_value(char *i, char **key_end, int is_dquote)
{
	char	*key_start;
	char	*key;
	char	*value;

	key_start = i + 1;
	*key_end = key_start;
	if (**key_end != '?' && **key_end != '_' && !ft_isalpha(**key_end))
		return (expand_env_value_exception(i, key_end, is_dquote));
	while (**key_end)
	{
		if (!*(*key_end + 1) || !is_valid_key_char(*(*key_end + 1)))
			break ;
		(*key_end)++;
	}
	key = ft_substr(key_start, 0, *key_end - key_start + 1);
	if (!key)
		return (NULL);
	value = get_env_value(key);
	free(key);
	return (value);
}

int	expand_tilde(t_token *curr)
{
	char	*home;
	char	*ret;

	if (!has_tilde(curr->data))
		return (FALSE);
	home = get_env_value("~");
	if (!home)
		return (ERROR);
	ret = ft_strjoin(home, curr->data + 1);
	free(home);
	if (!ret)
		return (ERROR);
	free(curr->data);
	curr->data = ret;
	return (TRUE);
}
