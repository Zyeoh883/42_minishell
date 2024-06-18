/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/18 15:24:23 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialise pipe int array
void	build_pipes(t_pipe *pipe_node) // * tested
{
	int	n;

	pipe_node->pipe = ft_calloc(2 * (pipe_node->n_nodes - 1), sizeof(int)); // ! leaks
	if_null_perror_n_exit(pipe_node->pipe, "ft_calloc", EXIT_FAILURE);
	n = -1;
	while (++n < pipe_node->n_nodes - 1)
		if (pipe(pipe_node->pipe + (2 * n)) == -1)
			perror_and_exit("pipe", EXIT_FAILURE);
}

// chooses input & output fd for a process
void	coupling(t_pipe *pipe_node, int n)
{
	if (n == 0) // first node
		dup2(pipe_node->pipe[1], STDOUT_FILENO);
	else if (n == pipe_node->n_nodes - 1) // last node
		dup2(pipe_node->pipe[2 * (n - 1)], STDIN_FILENO);
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
	while (++n < 2 * (pipe_node->n_nodes - 1))
		close(pipe_node->pipe[n]);
}

int do_pipe(t_pipe *pipe)
{
	pid_t pid;
	int n;
	pid_t pid_last;

	pid_last = -1;	
	build_pipes(pipe);
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
			exit(execute_ast(pipe->arr_nodes[n]));
		}
		if (n == pipe->n_nodes - 1) // ?: don't need? can just use pid (parent's pid represent child's)
			pid_last = pid;
	}
	close_pipes(pipe);
	return (pid_last); // * returns last child pid
}

int	execute_pipe(t_pipe *pipe)
{
	int exit_status;
	int pid_last;

	pid_last = do_pipe(pipe);

	// * WAIT
	exit_status = waitpid_n_get_exit_status(pid_last);
	while (waitpid(-1, NULL, 0) != -1)
		;
	return (exit_status);
}

	// while (1)
	// {
	// 	int exited_pid = waitpid(-1, NULL, 0); // !
	// 	if (exited_pid == -1)
	// 		break ;
	// 	else 
	//     	printf(YELLOW"Child process with PID %d has exited."RESET"\n", exited_pid);
	// }