/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_draft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/04/25 16:01:21 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
* TO NOTE
*----------------
- each execute_subfunction will return SUCCESS/FAIL

*/

/*
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
*/


int execute_simple_cmd(t_simple_command *sc)
{
	// setup_redir(simple_cmd->redir);

	if (sc->is_built_in) 
	{
		//execute_built_in()
	}
	else 
	{
		if (execute_execve(sc->cmd, sc->env) == FAIL)
			return (FAIL);
	}
	return (SUCCESS);
}

// int execute_and_or(t_and_or *andor) // ! not done - LOGIC INCORRECT
// {
	// int i;
	// int j;

	// i = -1;
	// j = -1;
	// while (andor->arr_nodes[++i] != NULL)
	// {
	// 	if (andor->operators[++j] == AND) // ! separated index for operator?
	// 	{
	// 		if (execute(andor->arr_nodes[i]) == SUCCESS)
	// 		{
	// 			continue;
	// 		}
	// 		else // FAILURE
	// 		{
	// 			i++; // skip next node
	// 		}
	// 	}
	// 	else if (andor->operators[i] == OR)
	// 	{
	// 		if (execute(andor->arr_nodes[i]) == SUCCESS)
	// 		{
	// 			i++;
	// 		}
	// 		else // FAILURE
	// 		{
	// 			continue; // skip next node
	// 		}
	// 	}
	// }
// }

int execute_subshell(t_subshell *subshell)
{
	pid_t pid;
	
	pid = fork();
	if (pid == -1)
	{
		// error handling
	}
	else if (pid == 0) // * CHILD
	{
		if (execute(subshell->node) == FAIL)
			return (FAIL);
	}
	// else if (pid > 0)
	// {
	 	// waitpid(0, NULL, 0); // ! need to wait?
	// }
	return (SUCCESS);
}


// return SUCCESS/FAILURE to tell execute_and_or()
int execute(t_node *node)
{
    // if (node->type == AND_OR)
    //     // if (execute_and_or(node->and_or) == SUCCESS)
	// 	// 	return (SUCCESS);
    if (node->type == SUBSHELL)
	{
        if (execute_subshell(node->subshell) == SUCCESS)
			return (SUCCESS);
	}
    // else if (node->type == PIPE)
    //     if (execute_pipe(node->pipe) == SUCCESS)
	// 		return (SUCCESS);
	else if (node->type == SIMPLE_COMMAND)
	{
		if (execute_simple_cmd(node->simple_command) == SUCCESS)
			return (SUCCESS);
	}
	
	return (FAIL);
}
