/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:23 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/26 00:27:07 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(t_token *token)
{
	write(1, "\n", 1);
	while (token)
	{
		printf("Token: '%s' | type: %d\n", token->value, token->type);
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

t_token	*tokenize(char *line)
{
	t_token	*token_root;

	if (!line)
		return (NULL);
	token_root = tokenize_metacharacters(line);
	print_tokens(token_root);
	if (is_valid_token(token_root->next->next->next->next->next->next)) //index 6
		printf("%s in quote\n", token_root->next->next->next->next->next->next->value);
	else
		printf("%s not in quote\n", token_root->next->next->next->next->next->next->value);
	free_tokens(token_root);
	return (NULL);
}
