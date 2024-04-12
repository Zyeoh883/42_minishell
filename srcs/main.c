/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:57:53 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/12 20:58:47 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char **files;
	t_node *cmd;
	t_node *redir_in;

	(void)ac;
	(void)av;
	files = ft_calloc(3, sizeof(char *));
	files[0] = ft_strdup("file1");
	files[0] = ft_strdup("file2");
	cmd = create_command(env, "ls");
	redir_in = create_redir_in(env, files, cmd);

	execute(cmd);
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