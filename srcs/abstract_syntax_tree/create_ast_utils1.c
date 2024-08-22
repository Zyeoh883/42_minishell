/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:30:07 by Zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 11:03:07 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*find_top_closing_parent(t_token *token)
{
	int	open_count;

	open_count = 0;
	while (token)
	{
		if (token->type == CLOSED_PARENT && open_count < 2)
			return (token);
		else if (token->type == OPEN_PARENT)
			open_count++;
		else if (token->type == CLOSED_PARENT)
			open_count--;
		token = token->next;
	}
	return (NULL);
}

int	is_subshell(t_token *token_root)
{
	while (token_root && token_root->type == WHITESPACE)
		token_root = token_root->next;
	if (token_root && token_root->type == OPEN_PARENT)
		return (1);
	return (0);
}

int	is_and_or(t_token *token)
{
	if ((token->type == AND || token->type == OR) && !is_in_parentheses(token))
		return (1);
	return (0);
}

int	is_pipe_token(t_token *token)
{
	if (token->type == PIPES && !is_in_parentheses(token))
		return (1);
	return (0);
}

int	is_command_token(t_token *token)
{
	if (!is_file_token(token) && token->type == WORDS)
		return (1);
	return (0);
}
