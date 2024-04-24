/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:42:10 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/24 20:55:12 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*str_to_token(char *start, int len)
{
	t_token	*token;
	char	*value;

	value = ft_substr(start, 0, len);
	if (!value)
		perror_and_exit("malloc", 1);
	token = new_token(value);
	if (!token)
	{
		free(value);
		perror_and_exit("malloc", 1);
	}
	return (token);
}

void	free_tokens(t_token *token_root)
{
	t_token	*tmp;

	while (token_root)
	{
		tmp = token_root;
		token_root = token_root->next;
		free(tmp->value);
		free(tmp);
	}
}

void	token_add_back(t_token **token_root, t_token *new)
{
	t_token	*head;

	if (!*token_root)
	{
		*token_root = new;
		return ;
	}
	head = *token_root;
	while (head->next)
		head = head->next;
	head->next = new;
}

t_token	*new_token(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	return (token);
}

int	is_metacharacter(char c)
{
	char	*metacharacters;

	metacharacters = METACHARACTERS;
	while (*metacharacters)
	{
		if (c == *metacharacters)
			return (1);
		metacharacters++;
	}
	return (0);
}