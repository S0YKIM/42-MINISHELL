/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:36:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/17 14:11:11 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_env_key(char *i, char **key_end)
{
	char	*key_start;
	char	*key;
	char	*tmp;

	key_start = i + 1;
	*key_end = key_start;
	if (!(**key_end))
		return (ft_strdup("$"));
	if (ft_strchr("$\'\"", **key_end))
	{
		tmp = ft_strchr(*key_end, '\"');
		if (tmp)
			*key_end = tmp - 1;
		return (ft_substr(i, 0, *key_end - i + 1));
	}
	while (**key_end)
	{
		if (!*(*key_end + 1) || ft_strchr("$\'\"", *(*key_end + 1)))
			break ;
		(*key_end)++;
	}
	key = ft_substr(key_start, 0, *key_end - key_start + 1);
	return (key);
}

static char	*expand_new_token(t_data *data, t_token *curr, char *i, int *len)
{
	char	*key;
	char	*value;
	char	*key_end;
	char	*head;
	char	*new_token;

	key = find_env_key(i, &key_end);
	if (!key)
		return (NULL);
	value = get_env_value(data, key);
	free(key);
	if (!value)
		return (NULL);
	*i = '\0';
	head = ft_strjoin(curr->data, value);
	free(value);
	if (!head)
		return (NULL);
	*len = ft_strlen(head);
	new_token = ft_strjoin(head, key_end + 1);
	free(head);
	return (new_token);
}

static int	expand_and_replace(t_data *data, t_token *curr, char *i)
{
	int		len;
	char	*new_token;

	new_token = expand_new_token(data, curr, i, &len);
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
