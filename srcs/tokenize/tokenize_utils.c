/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:42:10 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/27 21:35:01 by zyeoh            ###   ########.fr       */
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

int	token_combine_wnext(t_token *token)
{
	t_token *head;
	char *new_value;

	if (!token || !token->next)
		return (0);
	new_value = ft_strjoin(token->value, token->next->value);
	if (!new_value)
		return (0);
	free(token->value);
	token->value = new_value;
	head = token->next->next;
	free(token->next->value);
	free(token->next);
	token->next = head;
	if (head)
		head->prev = token;
	return (1);
}
