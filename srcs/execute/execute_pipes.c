/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/12 16:45:09 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialise pipe int array
void	build_pipes(t_pipe *pipe_node)
{
	int n;

	pipe_node->pipe = ft_calloc(2 * (pipe_node->n_nodes - 1), sizeof(int));
	if_null_perror_n_exit(pipe_node->pipe, "ft_calloc", EXIT_FAILURE);
	n = -1;
	while (++n < pipe_node->n_nodes - 1)
		if (pipe(pipe_node->pipe + (2 * n)) == -1)
			perror_and_exit("pipe", EXIT_FAILURE);
}

void	coupling(t_pipe *pipe_node, int n)
		// child process chooses which pipe end to replace STDIN/OUT
{
	if (n == 0) // first node
	{
		dup2(pipe_node->pipe[1], STDOUT_FILENO);
	}
	else if (n == pipe_node->n_nodes - 1) // last node
	{
		dup2(pipe_node->pipe[2 * (n - 1)], STDIN_FILENO);
	}
	else // middle nodes
	{
		dup2(pipe_node->pipe[2 * (n - 1)], STDIN_FILENO);
		dup2(pipe_node->pipe[2 * n + 1], STDOUT_FILENO);
	}
}

void	close_pipes(t_pipe *pipe_node)
{
	int	n;

	n = -1;
	while (++n < pipe_node->n_nodes - 1)
		close(pipe_node->pipe[n]);
}

int	execute_pipe(t_pipe *pipe)
{
	// pid_t	pid;
	int		n;
	
	build_pipes(pipe);
	n = -1;
	// while (++n < pipe->n_nodes)
	// {
	// 	pid = fork();
	// 	if (pid == -1)
	// 		perror_and_exit("fork", EXIT_FAILURE);
	// 	if (pid == 0)
	// 	{
	// 		coupling(pipe, n);
	// 		close_pipes(pipe);
			// execute_ast(pipe->arr_nodes[n]);
	// 	}
	// }
	// TODO: in parent process -> close pipes, wait
	return (EXIT_SUCCESS);
}
