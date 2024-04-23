/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:23 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/23 20:13:03 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_instances(char *line, char *instance)
{
	char	*end;
	int		count;

	end = line + ft_strlen(line);
	count = 0;
	while (line < end)
	{
		line = ft_strnstr(line, instance, ft_strlen(line));
		if (!line || line >= end)
			break ;
		count++;
		line += ft_strlen(instance);
	}
	return (count);
}

void	token_add_back(t_token *tokens, t_token *new)
{
	if (!tokens)
		return (tokens = new);
	while (tokens->next)
		tokens = tokens->next;
	tokens->next = new;
}

t_token	*new_token(char *value, int type)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	return (token);
}

t_token	*tokenize_quotes(char *line)
{
	t_token	*tokens;
	char	*end;
	int		num_quotes;

	tokens = NULL;
	end = ft_strchr(line, '\"');
	if (!end)
		return (new_token(line, 0));
	num_quotes = count_instances(line, "\"");
}

t_token	*tokenize_line(char *line)
{
	t_token *tokens;

	if (!line)
		return (NULL);
	tokens = tokenize_quotes(line);
}