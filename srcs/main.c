/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:57:53 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 21:00:10 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*tokenize_pipe(char *input, char **env)
// basic argument parsing for testing
{
	char **test_commands;
	t_node *command;
	t_node **simple_cmd_arr;
	t_node *pipe_node;
	int size;
	int n;

	test_commands = ft_split(input, '|'); // get commands
	size = -1;
	while (test_commands[++size]) // pipe node needs number of commands for now, can change to null termination
		;
	if (size == 0)
		return (NULL);
	simple_cmd_arr = ft_calloc(size + 1, sizeof(t_node));
	// creates an array of nodes for the pipe node
	n = -1;
	while (++n < size)
	{
		// printf("test_commands[n] = %s\n", test_commands[n]);
		command = create_command(env, ft_split(test_commands[n], ' '));
		// creates command for simple command
		simple_cmd_arr[n] = create_simple_command(env, NULL, command);
		// create simple command
	}
	pipe_node = create_pipe(simple_cmd_arr, size);
	return (pipe_node);
}

int	main(int ac, char **av, char **env)
{
	t_node	*pipe;

	if (ac != 2)
	{
		printf("format error: ./minishell 'cmd0 | cmd1 | cmd2 | ..cmd{n}'\n");
		return (0);
	};
	pipe = tokenize_pipe(av[1], env);
	execute(pipe);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	char **files;
// 	char **cmd;
// 	t_node *command;
// 	t_node *simple_command;

// 	if (ac != 2)
// 	{
// 		printf("Testing with one string as input\n");
// 		return (0);
// 	};

// 	simple_command = tokenize_simple_command(av[1], env);
// 	execute(simple_command);

// 	files = ft_calloc(3, sizeof(char *));
// 	files[0] = ft_strdup("file1");
// 	files[1] = ft_strdup("file2");

// 	cmd = ft_calloc(3, sizeof(char *));
// 	cmd[0] = ft_strdup("ls");
// 	cmd[1] = ft_strdup("-l");
// 	command = create_command(env, cmd);
// 	simple_command = create_simple_command(env, files, command);

// 	execute(simple_command);

// 	return (0);
// }