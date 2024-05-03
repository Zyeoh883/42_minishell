/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/03 20:55:35 by zyeoh            ###   ########.fr       */
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

char	*handle_readline(char *str, int *status)
{
	char	*input;

	input = readline(str);
	if (input == NULL)
		perror_and_exit("readline", EXIT_FAILURE);
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

int	minishell_input(t_token **token_root)
{
	t_token	*token;
	char	*input;
	char	*line;
	int		status;

	line = NULL;
	input = handle_readline("minishell$ ", &status);
	while (status > 0)
	{
		token = tokenize(input);
		line = add_to_line(line, input);
		input = NULL;
		status = 0;
		if (!token)
			break ;
		token_add_back(token_root, token);
		if (is_token_open_ended(*token_root))
			input = handle_readline("> ", &status);
	}
	add_history(line);
	free(line);
	if (status == -1)
		free_tokens(*token_root);
	return (status);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
		return ;
	// printf("\nminishell reset\n");
	// exit(0);
}

int	main(int argc, char **argv, char **env)
{
	t_token	*token_root;
	int		status;

	// char	**my_env;
	(void)env;
	(void)argc;
	(void)argv;
	if (access("/tmp", F_OK) == -1)
		perror_and_return("access /tmp", EXIT_FAILURE);
	// if (signal(SIGINT, handle_sigint) == SIG_ERR)
	// {
	// 	perror("signal");
	// 	// return (EXIT_FAILURE);
	// }
	token_root = NULL;
	status = 1;
	while (status >= 0)
	{
		status = minishell_input(&token_root);
		print_tokens(token_root);
		free_tokens(token_root);
		token_root = NULL;
	}
	// free_str_arr(my_env);
	// system("leaks minishell");
	return (0);
}
// system("leaks minishell");