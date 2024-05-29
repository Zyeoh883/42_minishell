/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/21 14:50:21 by sting            ###   ########.fr       */
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
	t_var	*var_lst; // linked list

	var_lst = convert_env_to_linked_list(env);
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			perror_and_exit("readline", EXIT_FAILURE);
		add_history(input); // working history
		char **input_arr = ft_split(input, ' ');
		t_node	*node = create_simple_command(var_lst, input_arr);
		execute(node);

		free(input);
		free_str_arr(node->simple_command->cmd_arg);
		free(node->simple_command); // tmp
		free(node); // tmp

	}
	free_var_lst(var_lst); // ? needed?
}
