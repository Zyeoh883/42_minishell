/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:03:33 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/19 22:55:51 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	minishell_input(t_token **token_root)
// {
// 	t_token	*token;
// 	char	*input;

// 	g_signal = 0;
// 	input = readline("minishell$ ");
// 	if (!input || ft_strncmp("exit", input, 4) == 0)
// 		return (-1);
// 	token = tokenize(input);
// 	if (!token || g_signal == SIGINT)
// 		return (0);
// 	token_add_back(token_root, token);
// 	add_history(input);
// 	free(input);
// 	return (1);
// }

// int	minishell_input(t_token **token_root)
// {
// 	t_token	*token;
// 	char	*input;

// 	g_signal = 0;
// 	input = handle_readline("minishell$ ");
// 	if (ft_strncmp("exit", input, 4) == 0)
// 		return (-1);
// 	token = tokenize(input);
// 	if (!token || g_signal == SIGINT)
// 		return (0);
// 	token_add_back(token_root, token);
// 	add_history(input);
// 	free(input);
// 	return (1);
// }

int	minishell_input(t_token **token_root)
{
	t_token	*token;
	char	*input;
	char	*line;

	g_signal = 0;
	line = NULL;
	rl_done = 0;
	input = readline("minishell$ ");
	if (!input)
		exit(0);
	printf("inputed \n");
	while (input)
	{
		if (g_signal == SIGINT)
		{
			free(input);
			return (0);
		}
		token = tokenize(input);
		line = add_to_line(line, input);
		if (!token)
			break ;
		input = NULL;
		token_add_back(token_root, token);
		if (is_token_open_ended(*token_root))
			input = readline("> ");
		if (g_signal == SIGINT)
		{
			free(input);
			return (0);
		}
	}
	if (line && *line)
	{
		add_history(line);
		free(line);
	}
	return (1);
}

// char	*handle_readline(char *str, int *status)
// {
// 	char	*input;

// 	input = readline(str);
// 	if (g_signal == SIGINT)
// 		*status = 0;
// 	return (input);
// }

char	*add_to_line(char *line, char *input)
{
	int		size;
	char	*result;

	if (!line)
	{
		line = ft_strdup(input);
		if (!line)
			perror_and_exit("history", EXIT_FAILURE);
		free(input);
		return (line);
	}
	size = ft_strlen(line) + ft_strlen(input) + 2;
	result = ft_calloc(size, sizeof(char));
	if (!result)
		perror_and_exit("history", EXIT_FAILURE);
	ft_strlcat(result, line, size);
	ft_strlcat(result, " ", size);
	ft_strlcat(result, input, size);
	free(line);
	free(input);
	return (result);
}
