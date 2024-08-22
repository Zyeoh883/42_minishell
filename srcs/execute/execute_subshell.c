/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:23:08 by sting             #+#    #+#             */
/*   Updated: 2024/08/13 17:24:57 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_subshell(t_subshell *subshell, t_var *var_lst)
{
	pid_t	pid;

	if (open_redir_fds(subshell->redir, subshell->fd, var_lst) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		dup2_fdin_n_fdout(subshell->fd);
		exit(execute_ast(subshell->node));
	}
	return (waitpid_n_get_exit_status(pid));
}
	// ft_printf(CYAN ">>>>>SUBSHELL>>>>>" RESET "\n"); // ! remove
