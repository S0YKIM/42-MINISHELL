/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:36:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/17 16:20:31 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*expand_env_value(t_data *data, char *i, char **key_end)
{
	char	*key_start;
	char	*key;
	char	*value;

	key_start = i + 1;
	*key_end = key_start;
	if (!(**key_end) || ft_strchr("$\'\"", **key_end))
		return (expand_env_value_exception(i, key_end));
	while (**key_end)
	{
		if (!*(*key_end + 1) || ft_strchr("$\'\"", *(*key_end + 1)))
			break ;
		(*key_end)++;
	}
	key = ft_substr(key_start, 0, *key_end - key_start + 1);
	if (!key)
		return (NULL);
	value = get_env_value(data, key);
	free(key);
	return (value);
}

static int	expand_and_replace(t_data *data, t_token *curr, char *i)
{
	char	*value;
	char	*key_end;
	char	*head;
	int		len;
	char	*new_token;

	value = expand_env_value(data, i, &key_end);
	if (!value)
		return (ERROR);
	*i = '\0';
	head = ft_strjoin(curr->data, value);
	free(value);
	if (!head)
		return (ERROR);
	len = ft_strlen(head);
	new_token = ft_strjoin(head, key_end + 1);
	free(head);
	if (!new_token)
		return (ERROR);
	free(curr->data);
	curr->data = new_token;
	return (len);
}

static int	expand_env_quote(t_data *data, t_token *curr, char **i)
{
	char	*end;
	char	*dollar;
	int		len;

	end = ft_strchr(*i + 1, **i);
	if (!end)
		(*i)++;
	else if (end && **i == '\"')
	{
		dollar = ft_strchr(*i + 1, '$');
		if (dollar && dollar < end)
		{
			len = expand_and_replace(data, curr, dollar);
			if (len == ERROR)
				return (FALSE);
			*i = curr->data + len + 1;
		}
		else
			*i = end + 1;
	}
	else if (end && **i == '\'')
		*i = end + 1;
	return (TRUE);
}

int	expand_env(t_data *data, t_token *curr)
{
	char	*i;
	int		len;

	i = curr->data;
	len = 0;
	while (*i)
	{
		if (*i == '$')
		{
			len = expand_and_replace(data, curr, i);
			if (len == ERROR)
				return (FALSE);
			i = curr->data + len;
		}
		else if (*i == '\"' || *i == '\'')
		{
			if (!expand_env_quote(data, curr, &i))
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}
