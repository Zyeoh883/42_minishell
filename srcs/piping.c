/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 19:27:37 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 21:03:20 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_pipes(t_pipe *pipe_node) // creates the pipes for the forks to use later
{
	int	n;

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

void	coupling(t_pipe *pipe_node, int n) //child process chooses which pipe end to replace STDIN/OUT
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
