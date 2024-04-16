/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/16 09:23:02 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././inc/minishell.h"

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	char	*input;

	while (1)
	{
		input = readline("minishell$ ");	
		if (input == NULL)
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
		add_history(input);
		if (ft_strncmp("exit", input, 5) == 0)
		{
			free(input);
			exit(EXIT_SUCCESS);
		}
		t_node	*node = create_command(env, input);

		pid_t pid = fork();
		if (pid == 0)
			execute(node);
		else
		{
			free(input);
			waitpid(pid, NULL, 0);
		}
	}
}