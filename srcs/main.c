/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:57:53 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/10 17:29:32 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_node *node;

	(void)ac;
	(void)av;
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	node->type = COMMAND;
	node->command = (t_command *)ft_calloc(1, sizeof(t_command));
	node->command->str = "ls";
	node->command->env = env;

	execute(node);
	// after parsing all the inputs and making AST

	// node->type = PIPE;
	// node->pipe->n_nodes = 2;
	// node->pipe->arr_nodes = malloc (sizeof(t_node *) * 2);
	// node->pipe->fd_in = STDIN_FILENO;
	// node->pipe->fd_out = STDOUT_FILENO;
	// next = &node->pipe->arr_nodes[0];

	// char *line;
	// line = readline("minishell> ");
	// ft_printf(line);
	// free(line);
	return (0);
}