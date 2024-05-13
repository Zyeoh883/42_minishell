/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/05/13 15:43:38 by sting            ###   ########.fr       */
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
	// TODO: REDIRECTION setup_redir(simple_cmd->redir);
	print_str_arr(sc-> cmd, "Before quote_handling & Expansion"); // *print check
	handle_quotes_n_var_expansion(&sc->cmd, sc->var_lst);
	print_str_arr(sc->cmd, "ft_split_after_expansion"); // *print check

	// my_env = convert_var_lst_to_array(sc->var_lst); // ! transferred to execute_execve()

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
		return (execute_execve(sc->cmd, sc->var_lst)); // my_env is freed in this func
		// printf("exit_status: %i\n", ret);
	}
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
// int execute(t_node *node)
// {

//     // if (node->type == AND_OR)
//         // if (execute_and_or(node->and_or) == SUCCESS)
// 		// 	return (SUCCESS);
//     if (node->type == SUBSHELL)
//         return(execute_subshell(node->subshell));
//     // else if (node->type == PIPE)
//     //     if (execute_pipe(node->pipe) == SUCCESS)
// 	// 		return (SUCCESS);
// 	else if (node->type == SIMPLE_COMMAND)
// 		return(execute_simple_cmd(node->simple_command));
// 	else // INVALID NODE TYPE
// 		return (FAIL);
// }

// void set_exit_status(int exit_code, t_var *var_lst)
// {
// 	char *str;

// 	str = ft_itoa(exit_code);
// 	// printf("exit_status_str: %s\n", str);
// 	if_null_perror_n_exit(str, "ft_itoa", EXIT_FAILURE);
// 	set_var("?", str, var_lst);
// }

// idea to handle exit status
int execute(t_node *node)
{
	int ret;
    // if (node->type == AND_OR)
        // if (execute_and_or(node->and_or) == SUCCESS)
		// 	return (SUCCESS);
  	if (node->type == SUBSHELL)
		 ret = execute_subshell(node->subshell);
	else if (node->type == SIMPLE_COMMAND)
		ret = execute_simple_cmd(node->simple_command);
	else 
		ret = EXIT_FAILURE;
	// set_exit_status(ret, node->var_lst);
	return (ret);
}
