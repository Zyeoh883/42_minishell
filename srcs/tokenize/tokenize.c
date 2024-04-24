/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:56:23 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/24 20:28:50 by zyeoh            ###   ########.fr       */
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
	free_tokens(token_root);
	return (NULL);
}

// int	count_instances(char *line, char *instance)
// {
// 	char	*end;
// 	int		count;

// 	end = line + ft_strlen(line);
// 	count = 0;
// 	while (line < end)
// 	{
// 		line = ft_strnstr(line, instance, ft_strlen(line));
// 		if (!line || line >= end)
// 			break ;
// 		count++;
// 		line += ft_strlen(instance);
// 	}
// 	return (count);
// }

// t_token	*tokenize_quotes(char *line)
// {
// 	t_token	*tokens;
// 	char	*end;
// 	int		num_quotes;

// 	tokens = NULL;
// 	end = ft_strchr(line, '\"');
// 	if (!end)
// 		return (new_token(line, 0));
// 	num_quotes = count_instances(line, "\"");
// }

/*--------------------*/

// t_token	*tokenize_metacharacters(char *str)
// {
// 	int		flag;
// 	t_token	*token_root;
// 	t_token	*token;
// 	char	*start;
// 	char	*value;

// 	token_root = NULL;
// 	start = str;
// 	flag = 0;
// 	while (*str)
// 	{
// 		if (is_metacharacter(*str))
// 		{
// 			if (flag == 1)
// 			{
// 				value = ft_substr(start, 0, str - start);
// 				if (!value)
// 					perror_and_exit("malloc", 1);
// 				token = new_token(value, 0);
// 				if (!token)
// 					perror_and_exit("malloc", 1);
// 				token_add_back(&token_root, token);
// 				flag = 0;
// 			}
// 			value = ft_substr(str, 0, 1);
// 			if (!value)
// 				perror_and_exit("malloc", 1);
// 			token = new_token(value, 0);
// 			if (!token)
// 				perror_and_exit("malloc", 1);
// 			token_add_back(&token_root, token);
// 		}
// 		else if (flag == 0)
// 		{
// 			flag = 1;
// 			start = str;
// 		}
// 		str++;
// 	}
// 	if (flag == 1)
// 	{
// 		value = ft_substr(start, 0, str - start);
// 		if (!value)
// 			perror_and_exit("malloc", 1);
// 		token = new_token(value, 0);
// 		if (!token)
// 			perror_and_exit("malloc", 1);
// 		token_add_back(&token_root, token);
// 	}
// 	return (token_root);
// }