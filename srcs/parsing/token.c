/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heehkim <heehkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 19:11:57 by heehkim           #+#    #+#             */
/*   Updated: 2022/04/11 21:57:34 by heehkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 나중에 삭제!
// static void	display_token_list(t_data *data)
// {
// 	t_token	*curr;

// 	curr = data->token_list;
// 	while (curr)
// 	{
// 		printf("token: %s\n", curr->data);
// 		curr = curr->next;
// 	}
// }

void	free_token_list(t_data *data)
{
	t_token	*curr;
	t_token	*next;

	curr = data->token_list;
	while (curr)
	{
		next = curr->next;
		free(curr->data);
		free(curr);
		curr = next;
	}
	data->token_list = NULL;
}

static int	add_token_node(t_data *data, char *token)
{
	t_token	*new;
	t_token	*curr;

	new = (t_token *)ft_calloc(1, sizeof(t_token));
	if (!new)
		return (FALSE);
	new->data = token;
	if (!data->token_list)
		data->token_list = new;
	else
	{
		curr = data->token_list;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
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
			{
				free_token_list(data);
				return (FALSE);
			}
			start = end + 1;
		}
	}
	trim_token(data);
	// display_token_list(data);
	return (TRUE);
}
