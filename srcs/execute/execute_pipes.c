/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/12 13:53:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_pipes(t_pipe *pipe_node)
		// creates the pipes for the forks to use later
{
	int n;

	pipe_node->pipe = ft_calloc(2 * (pipe_node->n_nodes - 1), sizeof(int));
	if (!pipe_node->pipe) // TODO clean up error handling, ugly af
	{
		free(pipe_node);
		perror("pipe");
		return (0);
	}
	n = -1;
	while (++n < pipe_node->n_nodes - 1)
	{
		if (pipe(pipe_node->pipe + (2 * n)) == -1)
		{
			free(pipe_node->pipe);
			free(pipe_node);
			perror("pipe");
			return (0);
		}
	}
	return (1);
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
	pid_t	pid;
	int		n;

	n = -1;
	while (++n < pipe->n_nodes)
	{
		pid = fork();
		if (pid == -1)
			perror_and_exit("fork", EXIT_FAILURE);
		if (pid == 0)
		{
			coupling(pipe, n);
			close_pipes(pipe);
			execute_ast(pipe->arr_nodes[n]);
		}
	}
	return (EXIT_SUCCESS);
}

// int	execute_pipe(t_pipe *pipe)
// {
// 	int	i;

// 	// setup_all_pipes()
// 	i = -1;
// 	while (++i)
// 	{
// 		// fork
// 		// dup2() pipe ends
// 		//if (child_process)
// 			execute_ast(&pipe->arr_nodes[i]);
// 	}
// 	// wait() for all child processes
// }