/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:58:38 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:59:15 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_remove(t_token *token)
{
	t_token	*prev;
	t_token	*next;

	if (!token)
		return ;
	prev = token->prev;
	next = token->next;
	free(token->value);
	free(token);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

void	token_combine_wnext(t_token *token)
{
	char	*new_value;

	if (!token || !token->next)
		return ;
	new_value = ft_strjoin(token->value, token->next->value);
	if (!new_value)
		perror_and_exit("malloc error", EXIT_FAILURE);
	free(token->value);
	token->value = new_value;
	token_remove(token->next);
}

int	is_token_open_ended(t_token *token_root)
{
	t_token	*last;

	if (!token_root)
		return (0);
	last = token_last_nonspace(token_root);
	if (last->type == OPEN_PARENT)
		return (1);
	if (last->open_end || is_in_parentheses(last))
		return (1);
	if (PIPES <= last->type && last->type <= OR)
		return (1);
	return (0);
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
