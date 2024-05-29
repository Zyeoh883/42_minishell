/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/26 08:59:44 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ex_pipe(t_pipe *pipe)
{
	pid_t pid;
	int n;

	n = -1;
	while (++n < pipe->n_nodes)
	{
		pid = fork();
		if (pid == 0)
		{
			coupling(pipe, n);
			close_pipes(pipe);
			execute(pipe->arr_nodes[n]);
		}
	}
}
