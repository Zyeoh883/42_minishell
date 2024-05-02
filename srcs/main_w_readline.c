/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/03 01:17:22 by zyeoh            ###   ########.fr       */
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

int	handle_readline(char **input, int mode)
{
	if (mode == 0)
		*input = readline("minishell$ ");
	else
		*input = readline("> ");
	if (*input == NULL)
		return (perror_and_return("readline", 0));
	if (ft_strncmp("exit", *input, 5) == 0)
	{
		free(*input);
		return (0);
	}
	return (1);
}

int	minishell_input(t_token **token_root)
{
	char	*input;
	char	*line;
	t_token	*buffer;
	int		mode;

	mode = 0;
	input = NULL;
	while (handle_readline(&input, mode))
	{
		buffer = tokenize(input);
		free(input);
		if (!buffer)
			return (perror_and_return("Tokenization failed", 0));
		token_add_back(token_root, buffer);
		if (!is_token_open_ended(*token_root))
			break;
		mode = 1;
		print_tokens(*token_root);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	char	**my_env;
	t_token	*token_root;

	(void)argc;
	(void)argv;
	// pid_t	pid;
	// char	**cmd;
	if (access("/tmp", F_OK) == -1)
	{
		printf("minishell: /tmp: No such file or directory\n");
		return (1);
	}
	token_root = NULL;
	while (minishell_input(&token_root))
	{
		free_tokens(token_root);
	}

	free_tokens(token_root);
	// free_str_arr(my_env);
	return (0);
}
