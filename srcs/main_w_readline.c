/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/03 14:01:13 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env_copy(char **env)
{
	char	**my_env;
	int		num_env_vars;

	num_env_vars = -1;
	while (env[++num_env_vars] != NULL)
		;
	my_env = (char **)ft_calloc(num_env_vars + 1, sizeof(char *));
	if (my_env == NULL)
		perror_and_exit("malloc", EXIT_FAILURE);
	num_env_vars = -1;
	while (env[++num_env_vars] != NULL)
	{
		my_env[num_env_vars] = ft_strdup(env[num_env_vars]);
		if (!my_env[num_env_vars])
		{
			while (--num_env_vars >= 0)
				free(my_env[num_env_vars]);
			free(my_env);
			perror_and_exit("malloc", EXIT_FAILURE);
		}
	}
	return (my_env);
}

char *handle_readline(char *str)
{
	char *input;
	
	input = readline(str);
	if (input == NULL)
		perror_and_exit("readline", EXIT_FAILURE);
	if (ft_strncmp("exit", input, 5) == 0)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

char *add_to_line(char *line, char *input)
{
	char *result;
	char *temp;
	
	if (!line)
		return (ft_strdup(input));
	temp = ft_strjoin(" ", input);
	if (!temp)
	{
		free(line);
		return (NULL);
	}
	result = ft_strjoin(line, temp);
	free(line);
	free(temp);
	return (result);
}


t_token	*minishell_input(void)
{
	t_token *token_root;
	t_token	*token;
	char	*input;
	char	*line;

	line = NULL;
	token_root = NULL;
	input = handle_readline("minishell$ ");
	while (input)
	{
		token = tokenize(input);
		if (!token)
			perror_and_exit("tokenization", EXIT_FAILURE);
		line = add_to_line(line, input);
		if (!line)
			perror_and_exit("history", EXIT_FAILURE);
		free(input);
		input = NULL;
		token_add_back(&token_root, token);
		if (is_token_open_ended(token_root))
			input = handle_readline("> ");
	}
	add_history(line);
	free(line);
	return (token_root);
}

void temp()
{
	// char	**my_env;
	t_token	*token_root;

	// (void)env;
	// (void)argc;
	// (void)argv;
	if (access("/tmp", F_OK) == -1)
		perror_and_return("access /tmp", EXIT_FAILURE);
	while (1)
	{
		token_root = minishell_input();
		if (!token_root)
			break ;
		print_tokens(token_root);
		free_tokens(token_root);
	}
	// free_str_arr(my_env);
}

int	main(int argc, char **argv, char **env)
{
	// // char	**my_env;
	// t_token	*token_root;

	(void)env;
	(void)argc;
	(void)argv;
	temp();
	// if (access("/tmp", F_OK) == -1)
	// 	perror_and_return("access /tmp", EXIT_FAILURE);
	// while (1)
	// {
	// 	token_root = minishell_input();
	// 	if (!token_root)
	// 		break ;
	// 	print_tokens(token_root);
	// 	free_tokens(token_root);
	// }
	// // free_str_arr(my_env);
	system("leaks minishell");
	return (0);
}
// system("leaks minishell");