/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/18 15:08:51 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **create_env_copy(char **env)
{
	char	**my_env;
	int	len;

	int num_env_vars = -1;
	while (env[++num_env_vars] != NULL);

	my_env = (char **)malloc(sizeof(char *) * (num_env_vars + 1));
	if (my_env == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	int i = -1;
	while (env[++i] != NULL)
	{
		len = ft_strlen(env[i]) + 1;
		my_env[i] = (char *)malloc(len);
		ft_strlcpy(my_env[i], env[i], len);
	}
	my_env[num_env_vars] = NULL;
	return(my_env);
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
		input = readline("minishell$ ");	
		if (input == NULL)
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
		add_history(input); // working history
		if (ft_strncmp("exit", input, 5) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		t_node	*node = create_command(env, input);

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
}