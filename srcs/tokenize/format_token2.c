/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_token2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 10:52:00 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 10:52:33 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	format_whitespace(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == WHITESPACE)
		{
			while (token->next && token->next->type == WHITESPACE)
				token_remove(token->next);
		}
		token = token->next;
	}
}

void	label_tokens(t_token *token)
{
	while (token)
	{
		if (is_operand(*token->value) && ft_strlen(token->value) == 1)
		{
			if (*token->value == '>')
				token->type = REDIR_OUT;
			else if (*token->value == '<')
				token->type = REDIR_IN;
			else if (*token->value == '|')
				token->type = PIPES;
			else if (*token->value == '&')
				token->type = AMPERSAND;
			else if (*token->value == ' ')
				token->type = WHITESPACE;
			else if (*token->value == '(')
				token->type = OPEN_PARENT;
			else if (*token->value == ')')
				token->type = CLOSED_PARENT;
		}
		else if (is_banned_char(*token->value) && ft_strlen(token->value) == 1)
			token->type = 258;
		token = token->next;
	}
}
