/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_token1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:56:12 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 12:21:12 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// printf("%c to %c\n", token->value[0],
// 	token->value[ft_strlen(token->value) - 1]);
void	format_open_ends(t_token *token)
{
	while (token)
	{
		while (token->next && token->open_end == 1)
		{
			token_combine_wnext(token);
			if (token->value[0] == token->value[ft_strlen(token->value) - 1]
				&& ft_strlen(token->value) > 1)
			{
				token->open_end = 0;
			}
		}
		token = token->next;
	}
}

void	format_quotes(t_token *token)
{
	char	quote;

	while (token)
	{
		if (token && ft_strchr("'\"", *token->value)
			&& ft_strlen(token->value) == 1)
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

void	format_operands(t_token *token)
{
	while (token && token->next)
	{
		if (WHITESPACE < token->type && token->type < AND)
		{
			if (token->type == token->next->type)
			{
				token_combine_wnext(token);
				if (token->type == REDIR_OUT)
					token->type = REDIR_APPEND;
				else if (token->type == REDIR_IN)
					token->type = REDIR_HEREDOC;
				else if (token->type == PIPES)
					token->type = OR;
				else if (token->type == AMPERSAND)
					token->type = AND;
			}
			else if (token->type == REDIR_OUT && token->next->type == PIPES)
				token_combine_wnext(token);
		}
		token = token->next;
	}
}

void	format_words(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == WORDS && token->next->type == WORDS
			&& !token->next->open_end)
			token_combine_wnext(token);
		else
			token = token->next;
	}
}

void	format_tokens(t_token *token_root)
{
	t_token	*token;

	token = token_root;
	format_open_ends(token);
	format_quotes(token);
	label_tokens(token);
	format_whitespace(token);
	format_operands(token);
	format_words(token);
	format_words(token);
}
