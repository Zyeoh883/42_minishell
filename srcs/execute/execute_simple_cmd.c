/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_simple_cmd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 10:15:58 by sting             #+#    #+#             */
/*   Updated: 2024/06/07 16:14:48 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_simple_cmd(t_simple_command *sc)
{
	int	ret;

	ret = EXIT_SUCCESS;
	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
	// TODO: REDIRECTION 
	// get_redir(sc);
	ft_printf("===Output===\n");
	if (sc->cmd_arg == NULL) // no cmd at all
		return (EXIT_SUCCESS);
	ret = execute_builtins(sc);
	// close_opened_fds(sc->fd);
	if (ret == NOT_BUILTIN)
		return (execute_execve(sc));	
	return (ret);
}

// int	execute_simple_cmd(t_simple_command *sc)
// {	
// 	int redir_fd[2]; // 0 -> IN, 1 => OUT
// 	int fork;
	
// 	fork = OFF;
// 	handle_quotes_n_var_expansion(&sc->cmd_arg, sc->var_lst);
// 	open_redir_files(sc->redir, &redir_fd);
// 	if (sc->cmd_arg == NULL) // no cmd at all
// 		return (EXIT_SUCCESS);
// 	if (cd, unset, assignment, exit , export(with args))
// 		return (execute_builtin());
// 	else 
// 		fork = ON;
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			duping();
// 			close_fds();
// 			ret = execute_builtins(sc->cmd_arg, sc->var_lst);
// 			if (ret == NOT_BUILTIN)
// 				exit (execute_execve(sc->cmd_arg, sc->var_lst));
// 			exit (ret);
// 		}
// 		else if (pid > 0)
// 			return (waitpid_n_get_exit_status);		
// }