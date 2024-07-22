/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/07/22 16:29:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialise pipe (pid_t *)array , based on no. of nodes
void	build_pipes(t_pipe *pipe_node)
{
	int	n;

	pipe_node->pipe = ft_calloc(2 * (pipe_node->n_nodes - 1), sizeof(int));
	if_null_perror_n_exit(pipe_node->pipe, "ft_calloc", EXIT_FAILURE);
	n = -1;
	while (++n < pipe_node->n_nodes - 1)
		if (pipe(pipe_node->pipe + (2 * n)) == -1)
			perror_and_exit("pipe", EXIT_FAILURE);
}

// chooses/setup input & output fd for a process (dup2)
void	coupling(t_pipe *pipe_node, int n)
{
	if (n == 0)
		dup2(pipe_node->pipe[1], STDOUT_FILENO);
	else if (n == pipe_node->n_nodes - 1)
		dup2(pipe_node->pipe[2 * (n - 1)], STDIN_FILENO);
	else
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

int	do_pipe(t_pipe *pipe)
{
	pid_t	pid;
	int		n;

	pid = -1;
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
	}
	close_pipes(pipe);
	return (pid);
}

int	execute_pipe(t_pipe *pipe)
{
	int	exit_status;
	int	pid_last;

	pid_last = do_pipe(pipe);
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
//     	printf(YELLOW"Child process with PID %d has exited."RESET"\n",
// exited_pid);
// }