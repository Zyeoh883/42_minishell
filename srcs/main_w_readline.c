/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/22 18:49:00 by zyeoh            ###   ########.fr       */
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
	char	*input;
	char	**my_env;

	my_env = create_env_copy(env);
	while (1)
	{
		input = handle_readline();
		t_node	*node = create_command(env, ft_split(input, ' ')); // TODO remember to fix leaks

		printf("input: %s\n", node->command->cmd[0]);

		pid_t pid = fork(); // fork for each execution
		if (pid == 0)
			execute(node);
		else
		{
			free(input);
			waitpid(pid, NULL, 0);
		}
	}
	free_str_arr(my_env);
	return (0);
}
