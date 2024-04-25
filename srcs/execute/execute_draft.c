/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_draft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/04/25 11:04:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* GENERAL IDEA
*----------------
- each execute_subfunction will return SUCCESS/FAIL

*/

int execute_cmd(t_node	*words)
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
	// setup_all_pipes()
	
	int i = -1;
	while (++i)
	{
		// fork
		
		// dup2() pipe ends
		
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

int execute_simple_cmd(t_simple_command *simple_cmd)
{
	setup_redir(simple_cmd->redir);
	execute_cmd(simple_cmd->cmd);
}

int execute_and_or(t_and_or *andor) // ! not done - LOGIC INCORRECT
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (andor->arr_nodes[++i] != NULL)
	{
		if (andor->operators[++j] == AND) // ! separated index for operator?
		{
			if (execute(andor->arr_nodes[i]) == SUCCESS)
			{
				continue;
			}
			else // FAILURE
			{
				i++; // skip next node
			}
		}
		else if (andor->operators[i] == OR)
		{
			if (execute(andor->arr_nodes[i]) == SUCCESS)
			{
				i++;
			}
			else // FAILURE
			{
				continue; // skip next node
			}
		}
	}
}

int execute_subshell(t_subshell *subshell)
{
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
	{
		
	}
	else if (pid == 0) // * CHILD
	{
		execute(subshell->node);
	}
}
/*
- simple draft for "cmd + redir" combination only

*/


int execute(t_node *node)
{
    if (node->type == AND_OR)
        if (execute_and_or(node->and_or) == SUCCESS)
			return (SUCCESS);
    else if (node->type == SUBSHELL)
        if (execute_subshell(node->subshell) == SUCCESS)
			return (SUCCESS);
    else if (node->type == PIPE)
        if (execute_pipe(node->pipe) == SUCCESS)
			return (SUCCESS);
	else if (node->type == SIMPLE_COMMAND)
		if (execute_simple_cmd(node->simple_command) == SUCCESS)
			return (SUCCESS);
}
