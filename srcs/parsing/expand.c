/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 22:36:12 by heehkim           #+#    #+#             */
/*   Updated: 2022/05/01 20:43:46 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_token( \
	t_token *curr, char *value, char *key_start, char *key_end)
{
	char	*head;
	int		value_len;
	int		len;
	char	*new_token;

	*key_start = '\0';
	value_len = ft_strlen(value);
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

static int	expand_and_replace(t_token **curr, char *i, int is_dquote)
{
	char	*value;
	char	*key_end;
	int		len;
	char	*dollar;

	value = expand_env_value(i, &key_end, is_dquote);
	if (!value)
		return (ERROR);
	if (!*value && !*(key_end + 1))
		return (handle_invalid_env(curr, value, i));
	if (!is_dquote && ft_strchr(value, ' '))
		return (split_value_with_space(curr, value, i, key_end));
	len = replace_token(*curr, value, i, key_end);
	if (is_dquote && ft_strchr((*curr)->data + len, '$'))
	{
		dollar = ft_strchr((*curr)->data + len, '$');
		if (dollar < ft_strchr((*curr)->data, '\"'))
			len = dollar - (*curr)->data;
	}
	return (len);
}

static int	expand_env_quote(t_token **curr, char **i, char *end)
{
	char	*dollar;
	int		len;

	if (!end)
		(*i)++;
	else if (**i == '\'')
		*i = end + 1;
	else if (**i == '\"')
	{
		while (end && *i != end + 1)
		{
			dollar = ft_strchr(*i, '$');
			if (dollar && dollar < end)
			{
				len = expand_and_replace(curr, dollar, TRUE);
				if (len == ERROR)
					return (FALSE);
				*i = (*curr)->data + len;
				end = ft_strchr(*i, '\"');
			}
			else
				*i = end + 1;
		}
	}
	return (TRUE);
}

int	expand_env(t_token **curr)
{
	char	*i;
	int		len;

	i = (*curr)->data;
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
			if (!expand_env_quote(curr, &i, ft_strchr(i + 1, *i)))
				return (FALSE);
		}
		else
			i++;
	}
	return (TRUE);
}

int	expand(t_data *data, t_token **curr)
{
	t_token	*tmp;
	int		result;

	result = expand_tilde(*curr);
	if (result == ERROR)
		return (FALSE);
	else if (result)
	{
		*curr = (*curr)->next;
		return (CONTINUE);
	}
	result = expand_env(curr);
	if (!result)
		return (FALSE);
	else if (result == REMOVE)
	{
		tmp = (*curr)->next;
		delete_token_node(data, curr);
		*curr = tmp;
		return (CONTINUE);
	}
	return (TRUE);
}
