/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:23 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/02 21:56:31 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	write(1, "\n", 1);
	while (token)
	{
		printf("Token:  %-10s, type = %d, open = %d\n", token->value,
			token->type, token->open_end);
		token = token->next;
	}
	write(1, "\n", 1);
}

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

t_token	*tokenize_metacharacters(char *str)
{
	t_token	*token_root;
	t_token	*token;
	char	*start;

	token_root = NULL;
	while (*str)
	{
		if (!is_metacharacter(*str))
		{
			start = str;
			while (*str && !is_metacharacter(*str))
				str++;
			token = str_to_token(start, str - start);
		}
		else
		{
			token = str_to_token(str, 1);
			str++;
		}
		token_add_back(&token_root, token);
	}
	return (token_root);
}

int	validate_tokens(t_token *token_root)
{
	t_token	*token;
	int		here_doc_id;

	here_doc_id = 0;
	token = token_root;
	while (token)
	{
		if (!is_valid_token(token))
			return (0);
		if (is_here_doc(token))
		{
			if (!input_here_doc(token, here_doc_id))
				return (0);
			here_doc_id++;
		}
		token = token->next;
	}
	return (1);
}

t_token	*tokenize(char *line)
{
	t_token	*token;

	if (!line)
		return (NULL);
	// printf("token root is\n");
	// print_tokens(token_root);
	token = tokenize_metacharacters(line);
	// print_tokens(token);
	format_tokens(token);
	// print_tokens(token);
	if (!validate_tokens(token))
	{
		free_tokens(token);
		return (NULL);
	}
	// free_tokens(token_root);
	return (token);
}
