/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/05/29 14:35:54 by sting            ###   ########.fr       */
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


// int execute_simple_cmd(t_simple_command *sc)
// {
// 	// print_str_arr(sc-> cmd_arg, "Before quote_handling & Expansion"); // *print check
// 	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
// 	// print_str_arr(sc->cmd_arg, "ft_split_after_expansion"); // *print check
	
// 	// TODO: REDIRECTION setup_redir(simple_cmd->redir);

// 	printf("===Output===\n");
// 	if (sc->cmd_arg == NULL) // no cmd at all
// 		return (EXIT_SUCCESS);
// 	else if (sc->is_built_in)
// 		return (execute_builtins(sc->cmd_arg, sc->var_lst));
// 	else
// 		return (execute_execve(sc->cmd_arg, sc->var_lst));
// }

int execute_simple_cmd(t_simple_command *sc)
{
	int ret_builtin;
	// print_str_arr(sc-> cmd_arg, "Before quote_handling & Expansion"); // *print check
	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
	// print_str_arr(sc->cmd_arg, "ft_split_after_expansion"); // *print check
	
		
	// TODO: REDIRECTION setup_redir(simple_cmd->redir);

	printf("===Output===\n");
	if (sc->cmd_arg == NULL) // no cmd at all
		return (EXIT_SUCCESS);
	ret_builtin = execute_builtins(sc->cmd_arg, sc->var_lst);
	if (ret_builtin == NOT_BUILTIN)
		return (execute_execve(sc->cmd_arg, sc->var_lst));
	else
		return (ret_builtin);
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
	return (EXIT_SUCCESS);
}

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
	set_exit_status(ret, node->var_lst);
	return (ret);
}
