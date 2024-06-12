/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:34:17 by sting             #+#    #+#             */
/*   Updated: 2024/06/12 13:45:47 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





int	execute_ast(t_node *node)
{
	int	ret;

	// if (node->type == AND_OR)
	// if (execute_and_or(node->and_or) == SUCCESS)
	// 	return (SUCCESS);
	if (node->type == SUBSHELL)
		ret = execute_subshell(node->subshell);
	else if (node->type == PIPE)
		ret = execute_pipe(node->pipe);
	else if (node->type == SIMPLE_COMMAND)
		ret = execute_simple_cmd(node->simple_command);
	else
		ret = EXIT_FAILURE;
	set_exit_status(ret, node->var_lst);
	return (ret);
}
