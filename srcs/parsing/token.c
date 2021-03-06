/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:11:57 by heehkim           #+#    #+#             */
/*   Updated: 2022/05/04 01:28:08 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_token_node(t_data *data, char *token)
{
	t_token	*new;
	t_token	*curr;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (FALSE);
	new->data = token;
	if (!ft_strchr("<>|", *token))
		new->is_word = TRUE;
	if (!data->token_list)
		data->token_list = new;
	else
	{
		curr = data->token_list;
		while (curr->next)
			curr = curr->next;
		new->prev = curr;
		curr->next = new;
	}
	return (TRUE);
}

int	insert_token_node(t_token **curr, char *data)
{
	t_token	*new;

	if (!data)
		return (FALSE);
	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (FALSE);
	new->data = data;
	new->is_word = TRUE;
	new->next = (*curr)->next;
	new->prev = (*curr);
	(*curr)->next = new;
	if (new->next)
		new->next->prev = new;
	return (TRUE);
}

static char	*find_end(char *start)
{
	char	*end;
	char	*tmp;

	end = start;
	tmp = NULL;
	while (*end && *start != '|')
	{
		if (ft_strchr("<>", *end))
		{
			if (*end == *(end + 1))
				end++;
			break ;
		}
		if (ft_strchr("\"\'", *end))
		{
			tmp = ft_strchr(end + 1, *end);
			if (tmp)
				end = tmp;
		}
		if (!*(end + 1) || ft_strchr(" |<>", *(end + 1)))
			break ;
		end++;
	}
	return (end);
}

int	tokenize(t_data *data, char *line)
{
	char	*start;
	char	*end;
	char	*token;

	start = line;
	while (*start)
	{
		while (ft_isspace(*start))
			start++;
		end = find_end(start);
		if (*end)
		{
			token = ft_substr(start, 0, end - start + 1);
			if (!token || !add_token_node(data, token))
				return (FALSE);
			start = end + 1;
		}
	}
	if (!trim_token(data))
		return (FALSE);
	return (TRUE);
}
