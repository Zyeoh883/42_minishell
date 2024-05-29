/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draft_main_workingexit.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/03 18:24:50 by zyeoh            ###   ########.fr       */
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

char	*handle_readline(char *str)
{
	char	*input;

	input = readline(str);
	if (input == NULL)
		perror_and_exit("readline", EXIT_FAILURE);
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

char	*minishell_input(void)
{
	t_token	*token;
	char	*input;
	char	*line;

	line = NULL;
	input = handle_readline("minishell$ ");
	while (1)
	{
		if (!input)
			break ;
		token = tokenize(input);
		line = add_to_line(line, input);
		if (!token)
			break ;
		input = NULL;
		if (is_token_open_ended(token))
			input = handle_readline("> ");
		free_tokens(token);
	}
	add_history(line);
	return (line);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
		printf("\nminishell reset\n");
	// exit(0);
}

void temp()
{
	t_token	*token_root;
	char	*line;

	if (access("/tmp", F_OK) == -1)
		perror_and_return("access /tmp", EXIT_FAILURE);
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
	{
		perror("signal");
		// return (EXIT_FAILURE);
	}
	token_root = NULL;
	while (1)
	{
		line = minishell_input();
		if (ft_strncmp("exit", line, 5) == 0)
			break ;
		token_root = tokenize(line);
		free(line);
		// if (!token_root)
		// 	break ;
		print_tokens(token_root);
		free_tokens(token_root);
		token_root = NULL;
	}
	free(line);
}

int	main(int argc, char **argv, char **env)
{
	// t_token	*token_root;
	// char	*line;

	// char	**my_env;
	(void)env;
	(void)argc;
	(void)argv;
	// if (access("/tmp", F_OK) == -1)
	// 	perror_and_return("access /tmp", EXIT_FAILURE);
	// if (signal(SIGINT, handle_sigint) == SIG_ERR)
	// {
	// 	perror("signal");
	// 	// return (EXIT_FAILURE);
	// }
	// token_root = NULL;
	// while (1)
	// {
	// 	line = minishell_input();
	// 	if (ft_strncmp("exit", line, 5) == 0)
	// 		break ;
	// 	token_root = tokenize(line);
	// 	free(line);
	// 	// if (!token_root)
	// 	// 	break ;
	// 	print_tokens(token_root);
	// 	free_tokens(token_root);
	// 	token_root = NULL;
	// }
	temp();
	// free_str_arr(my_env);
	system("leaks minishell");
	return (0);
}
// system("leaks minishell");