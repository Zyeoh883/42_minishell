/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/04/15 11:20:40 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././inc/minishell.h"

int execute_cmd(t_cmd *cmd)
{
	char **args;

	/*
	loop through "cmd" linked list if there're args
		- transfer strings into args variable
	*/

	// callexecve()
}

/*

str
*/
int execute_pipe(t_pipe *pipe)
{
	// setup all pipes
	
	int i = -1;
	while (++i)
	{
		// fork
		
		//if (child_process)
			execute(&pipe->arr_nodes[i]);
	}

	// wait() for all child processes
}

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

int execute_simple_cmd(t_simple_cmd *simple_cmd)
{
	setup_redir(simple_cmd->redir); // ! should dup2 be done after forking/in child process
	execute_cmd(simple_cmd->words);
}

/*
- simple draft for "cmd + redir" combination only

*/
int execute(t_node *node)
{
	if (node->type == SIMPLE_CMD)
	{
		// setup_redir(node->redir);
		// // execute(node->command); // ! incorrect input type
        // execute_cmd(node->words);
		execute_simple_cmd(node->simple_cmd);

	}
    else if (node->type == COMMAND)
        execute_cmd(node->command);
    else if (node->type == PIPE)
        execute_pipe(node->pipe);
}
