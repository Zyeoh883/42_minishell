/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/07/04 10:37:11 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		execute_ast(node);

		free(input);
		free_str_arr(node->simple_command->cmd_arg);
		free(node->simple_command); // tmp
		free(node); // tmp

	}
	free_var_lst(var_lst); // ? needed?
}
