/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:03:33 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/03 18:44:48 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_input(t_token **token_root)
{
	char	*input;

	input = readline("minishell$ ");
	// printf("continue\n");
	if (!input) // ft_strncmp("exit", input, 4) == 0
		return (-1);
	if (g_signal == SIGINT)
	{
		free(input);
		return (0);
	}
	*token_root = tokenize(input, NULL);
	if (!*token_root)
		return (0);
	input = handle_addon(input, *token_root);
	if (!input)
		return (0);
	add_history(input);
	free(input);
	return (1);
}

char	*handle_addon(char *input, t_token *token_root)
{
	t_token	*token;
	char	*input_addon;
	char	hanging_char;

	while (is_token_open_ended(token_root))
	{
		input_addon = readline("> ");
		hanging_char = *(token_last_nonspace(token_root)->value);
		if (!input_addon || g_signal == SIGINT)
		{
			if (!input_addon)
				output_eof_error(hanging_char);
			add_history(input);
			free(input);
			free(token_root);
			return (NULL);
		}
		input_addon = pad_input_addon(token_root, input_addon);
		token = tokenize(input_addon, token_root);
		print_tokens(token);
		if (!token)
			return (NULL);
		input = add_to_line(input, input_addon);
	}
	return (input);
}

char	*pad_input_addon(t_token *token_root, char *input_addon)
{
	char	*result;
	int		size;
	char	hanging_char;

	hanging_char = *(token_last_nonspace(token_root)->value);
	size = ft_strlen(input_addon) + 2;
	result = ft_calloc(size, sizeof(char));
	if (!result)
		perror_and_exit("malloc", EXIT_FAILURE);
	if (ft_strchr("'\"", hanging_char))
		result[0] = '\n';
	else
		result[0] = ' ';
	ft_strlcat(result, input_addon, size);
	free(input_addon);
	return (result);
}

char	*add_to_line(char *input, char *add_on)
{
	int		size;
	char	*result;

	if (!input)
		return (add_on);
	size = ft_strlen(input) + ft_strlen(add_on) + 1;
	result = ft_calloc(size, sizeof(char));
	if (!result)
		perror_and_exit("history", EXIT_FAILURE);
	ft_strlcat(result, input, size);
	ft_strlcat(result, add_on, size);
	free(input);
	free(add_on);
	return (result);
}
