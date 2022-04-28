/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:36:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/28 21:38:03 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_value_with_space( \
	t_token **curr, char *value, char *key_start, char *key_end)
{
	char	**arr;
	int		i;
	int		len;
	char	*tmp;

	if (*(key_end + 1))
	{
		if (!insert_token_node(curr, ft_strdup(key_end + 1)))
			return (ERROR);
	}
	arr = ft_split(value, ' ');
	if (!arr)
		return (ERROR);
	// 키 앞에 내용이 있으면 curr->data substr
	if ((*curr)->data != key_start)
	{
		tmp = (*curr)->data;
		(*curr)->data = ft_substr(tmp, 0, key_start - tmp);
		free(tmp);
		i = 0;
	}
	else
	{
		// 키 앞에 내용이 없으면
		free((*curr)->data);
		(*curr)->data = ft_strdup(arr[0]);
		i = 1;
	}
	if (!(*curr)->data)
		return (ERROR);
	while (arr[i])
	{
		if (!insert_token_node(curr, ft_strdup(arr[i])))
			return (ERROR);
		i++;
		*curr = (*curr)->next;
	}
	*curr = (*curr)->prev;
	len = ft_strlen(arr[i - 1]);
	free_double_pointer(arr);
	return (len);
}

static int	expand_and_replace(t_token **curr, char *i, int is_dquote)
{
	char	*value;
	char	*key_end;
	char	*head;
	int		len;
	char	*new_token;

	value = expand_env_value(i, &key_end, is_dquote);
	if (!value)
		return (ERROR);
	if (!is_dquote && !*value)
		return (REMOVE);
	if (!is_dquote && ft_strchr(value, ' '))
		return (split_value_with_space(curr, value, i, key_end));
	*i = '\0';
	head = ft_strjoin((*curr)->data, value);
	free(value);
	if (!head)
		return (ERROR);
	len = ft_strlen(head);
	new_token = ft_strjoin(head, key_end + 1);
	free(head);
	if (!new_token)
		return (ERROR);
	free((*curr)->data);
	(*curr)->data = new_token;
	return (len);
}

static int	expand_env_quote(t_token **curr, char **i)
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
			len = expand_and_replace(curr, dollar, TRUE);
			if (len == ERROR)
				return (FALSE);
			*i = (*curr)->data + len + 1;
		}
		else
			*i = end + 1;
	}
	else if (end && **i == '\'')
		*i = end + 1;
	return (TRUE);
}

int	expand_env(t_token **curr)
{
	char	*i;
	int		len;

	i = (*curr)->data;
	len = 0;
	while (*i)
	{
		if (*i == '$')
		{
			len = expand_and_replace(curr, i, FALSE);
			if (len == ERROR)
				return (FALSE);
			if (len == REMOVE)
				return (REMOVE);
			i = (*curr)->data + len;
		}
		else if (*i == '\"' || *i == '\'')
		{
			if (!expand_env_quote(curr, &i))
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}
