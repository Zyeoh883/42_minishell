/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:59:30 by sting             #+#    #+#             */
/*   Updated: 2024/06/25 16:47:08 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! NORM
int	execute_echo(t_simple_command *sc)
{
	pid_t	pid;
	int		i;
	int		n_flag;

	pid = fork();
	if (pid < 0)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2_fdin_n_fdout(sc->fd);
		n_flag = OFF;
		if (sc->cmd_arg[1] && ft_strcmp(sc->cmd_arg[1], "-n") == 0)
			n_flag = ON;
		i = 0;
		if (n_flag == ON)
			i++;
		while (sc->cmd_arg[++i] != NULL)
		{
			ft_putstr_fd(sc->cmd_arg[i], STDOUT_FILENO);
			if (sc->cmd_arg[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
		}
		if (n_flag == OFF)
			ft_putstr_fd("\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	return (waitpid_n_get_exit_status(pid));
}

