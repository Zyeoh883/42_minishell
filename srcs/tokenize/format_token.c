/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:56:12 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/28 03:50:29 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void format_quotes(t_token *token)
{
	char quote;

	while (token)
	{
		if (ft_strchr("'\"", *token->value))
		{
			quote = *token->value;
			while (token->next && *token->next->value != quote)
				token_combine_wnext(token);
			if (!token->next)
				token->open_end = 1;
			token_combine_wnext(token);
		}
		token = token->next;
	}
}

void format_parenthesis(t_token *token)  // TODO Fix order of enclosure
{
	while (token)
	{
		if (*token->value == '(')
		{
			while (token->next && *token->next->value != ')' && *token->next->value != '(')
				token_combine_wnext(token);
			if (!token->next)
				token->open_end = 1;
			token_combine_wnext(token);
		}
		token = token->next;
	}
}

void format_whitespace(t_token *token)
{
	while (token)
	{
		if (ft_strchr(" ", *token->value))
		{
			while (token->next && *token->next->value == ' ')
				token_remove(token->next);
		}
		token = token->next;
	}
}

void	format_tokens(t_token *token_root)
{
	t_token	*token;

	token = token_root;
	format_quotes(token);
	format_whitespace(token);
	// format_parenthesis(token); // TODO figure when to call this, token validator works for tokens only
	printf("\n\n");
}
