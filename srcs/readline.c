/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:03:33 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/15 22:53:10 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_input(t_token **token_root)
{
	t_token	*token;
	char	*input;
	char	*line;
	int		status;

	line = NULL;
	status = 1;
	input = handle_readline("minishell$ ", &status);
	while (status > 0)
	{
		if (g_signal == SIGINT)
		{
			free(input);
			g_signal = 0;
			return;
		}
		token = tokenize(input);
		line = add_to_line(line, input);
		if (!token)
			break ;
		input = NULL;
		status = 0;
		token_add_back(token_root, token);
		if (is_token_open_ended(*token_root))
			input = handle_readline("> ", &status);
	}
	add_history(line);
	free(line);
	if (status == -1)
		free_tokens(*token_root);
}

char	*handle_readline(char *str, int *status)
{
	char	*input;

	input = readline(str);
	if (input == NULL)
		perror_and_exit("readline", EXIT_FAILURE); // TODO dont show 'ˆD' on terminal
	printf("input return is %p\n", input);
	if (ft_strncmp("exit", input, 5) == 0)
	{
		free(input);
		*status = -1;
		return (NULL);
	}
	*status = 1;
	return (input);
}

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
