/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:03:33 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/06 16:04:23 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	minishell_input(t_data	*shell_data) // TODO function too long
{
	char	*input;

	input = readline("minishell$ ");
	if (!input)
		return (-1);
	if (g_signal == SIGINT || ft_strlen(input) == 0)
	{
		if (ft_strlen(input) == 0)
			set_exit_status(0, shell_data->var_lst);
		free(input);
		return (0);
	}
	shell_data->token_root = tokenize(input, NULL);
	input = handle_addon(input, shell_data->token_root);
	if (!shell_data->token_root || !input)
	{
		free(input);
		set_exit_status(TOKEN_FAIL, shell_data->var_lst);
		return (0);
	}
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

	if (ft_strlen(input_addon) == 0)
		return (input_addon);
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
