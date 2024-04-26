/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/26 13:31:33 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char **create_env_copy(char **env)
// {
// 	char	**my_env;
// 	int	len;

// 	int num_env_vars = -1;
// 	while (env[++num_env_vars] != NULL);

// 	my_env = (char **)malloc(sizeof(char *) * (num_env_vars + 1));
// 	if (my_env == NULL)
// 	{
// 		perror("malloc");
// 		exit(EXIT_FAILURE);
// 	}
// 	int i = -1;
// 	while (env[++i] != NULL)
// 	{
// 		len = ft_strlen(env[i]) + 1;
// 		my_env[i] = (char *)malloc(len);
// 		ft_strlcpy(my_env[i], env[i], len);
// 	}
// 	my_env[num_env_vars] = NULL;
// 	return(my_env);
// }


int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*input;
	char	**my_env;

	t_env_var	*env_var; // linked list

	// TODO create linked_list for env

	env_var = convert_env_to_linked_list(env);

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
		t_node	*node = create_simple_command(env, ft_split(input, ' '));


		execute(node);
		// ^error check?
	}
	
	free_str_arr(my_env);
}