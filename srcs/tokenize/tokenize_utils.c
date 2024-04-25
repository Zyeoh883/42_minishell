/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:42:10 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/26 00:05:16 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	new->prev = head;
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

t_token	*token_last(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*token_last_nonspace(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		if (*head->value != ' ')
			token = head;
		head = head->next;
	}
	return (token);
}
