/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/04/12 17:22:26 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_cmd(t_cmd *cmd)
{
	char **args;

	/*
	loop through "cmd" linked list if there're args
		- transfer strings into args variable
	*/

	// callexecve()
}

// int execute_pipe(t_pipe *pipe)
// {

// }

int setup_redir(t_redir	*redir)
{
	if (redir->type == INPUT)
	{
		// open()
		// dup2()
	}
	else
	{
		// open()
		// dup2()
	}

}

/*
- simple draft for "cmd + redir" combination only

*/
int execute(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		setup_redir(node->redir);
		execute(node->command);
	}
    else if (node->type == COMMAND)
        execute_cmd(node->command);
    else if (node->type == PIPE)
        execute_pipe(node->pipe);
}
