/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/08 13:52:44 by sting            ###   ########.fr       */
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
	t_env_var	*env_lst; // linked list

	env_lst = convert_env_to_linked_list(env);
	while (1)
	{
		input = readline("minishell$ ");	
		if (input == NULL)
			perror_and_exit("readline", EXIT_FAILURE);
		add_history(input); // working history
		if (ft_strncmp("exit", input, 5) == 0)
		{
			free(input);
			free_env_lst(env_lst);
			exit(EXIT_SUCCESS);
		}
		char **input_arr = ft_split(input, ' ');
		t_node	*node = create_simple_command(env_lst, input_arr);
		execute(node); 
		// ^error check?
		
		// free_str_arr(input_arr);
		free(input);
		if (node->simple_command->cmd)
			free_str_arr(node->simple_command->cmd); // ! SEGV when i uncomment this
		
		free(node->simple_command); // tmp
		free(node); // tmp

	}
	free_env_lst(env_lst); // ? needed?

}