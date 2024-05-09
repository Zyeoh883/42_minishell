/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/05/09 14:14:23 by sting            ###   ########.fr       */
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
	char **my_env;
	int ret;

	// TODO: REDIRECTION setup_redir(simple_cmd->redir);
	my_env = convert_env_lst_to_array(sc->env_lst);
	print_str_arr(sc-> cmd, "Before quote_handling & Expansion"); // *print check
	handle_quotes_n_var_expansion(&sc->cmd, my_env);
	print_str_arr(sc->cmd, "ft_split_after_expansion"); // *print check


	ret = SUCCESS;
	if (sc->cmd == NULL) // no cmd at all
		return (SUCCESS);
	else if (sc->is_built_in)
	{
		//ret = execute_built_in(sc->env_lst) // free my_env in this func
		return (SUCCESS); // ! temporary here
	}
	else
	{
		printf("===Output===\n");
		ret = execute_execve(sc->cmd, my_env); // my_env is freed in this func
		printf("exit_status: %i\n", ret);
	}
	free(my_env);
	return(ret);
}
/*
* if (execute() > 0) => FAIL
* if (execute() == 0) => SUCCESS
*/
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
		return(execute(subshell->node));
	// else if (pid > 0)
	// {
	 	// waitpid(0, NULL, 0); // ! need to wait?
	// }
	return (SUCCESS);
}

// return value is exit code
int execute(t_node *node)
{
    // if (node->type == AND_OR)
        // if (execute_and_or(node->and_or) == SUCCESS)
		// 	return (SUCCESS);
    if (node->type == SUBSHELL)
        return(execute_subshell(node->subshell));
    // else if (node->type == PIPE)
    //     if (execute_pipe(node->pipe) == SUCCESS)
	// 		return (SUCCESS);
	else if (node->type == SIMPLE_COMMAND)
		return(execute_simple_cmd(node->simple_command));
	else // INVALID NODE TYPE
		return (FAIL);
}

// idea to handle exit status
// int execute(t_node *node, int *final_exit_status)
// {

//     // if (node->type == AND_OR)
//         // if (execute_and_or(node->and_or) == SUCCESS)
// 		// 	return (SUCCESS);
//   if (node->type == SUBSHELL)
// 	{
// 		  *final_exit_status = execute_subshell(node->subshell);
//       if (*final_exit_status == SUCCESS)
// 				return (SUCCESS);
// 	}
//     // else if (node->type == PIPE)
//     //     if (execute_pipe(node->pipe) == SUCCESS)
// 	// 		return (SUCCESS);
// 	else if (node->type == SIMPLE_COMMAND)
// 	{
// 			*final_exit_status = execute_simple_cmd(node->simple_command);
// 	    if (*final_exit_status == SUCCESS)
// 				 return (SUCCESS);
// 	}
// 	return (*final_exit_status);
// }
