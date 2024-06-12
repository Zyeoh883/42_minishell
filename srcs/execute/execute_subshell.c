/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:23:08 by sting             #+#    #+#             */
/*   Updated: 2024/06/12 13:15:19 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_subshell(t_subshell *subshell)
{
	pid_t	pid;

	ft_printf(CYAN ">>>>>SUBSHELL>>>>>" RESET "\n"); // ! remove
	pid = fork();
	if (pid == -1)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
		exit(execute_ast(subshell->node));
	return (waitpid_n_get_exit_status(pid));
}
