/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/28 02:30:54 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_env_copy(char **env)
{
	char	**my_env;
	int num_env_vars;
	
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
	return(my_env);
}

char *handle_readline()
{
	char	*input;

	input = readline("minishell$ ");	
	if (input == NULL)
		perror_and_exit("readline", EXIT_FAILURE);
	add_history(input); // working history
	if (ft_strncmp("exit", input, 5) == 0)
	{
		free(input);
		exit(EXIT_SUCCESS);
	}
	return (input);
}

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	// pid_t	pid;
	// char	**cmd;
	char	*input;
	char	**my_env;

	my_env = create_env_copy(env);
	while (1)
	{
		input = handle_readline();
		tokenize(input);
		// cmd = ft_split(input, ' ');
		// t_node	*node = create_simple_command(env, NULL, cmd, 0); // TODO free node after

		// pid = fork(); // fork for each execution
		// if (pid == 0)
		// {
		// 	(void)node;
		// 	exit(0);
		// 	// execute(node);
		// }
		// else
		// {
		// 	free_split(cmd);
		// 	free(input);
		// 	waitpid(pid, NULL, 0);
		// }
	}
	free_str_arr(my_env);
	return (0);
}
