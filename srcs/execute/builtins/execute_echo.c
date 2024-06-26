/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:59:30 by sting             #+#    #+#             */
/*   Updated: 2024/06/26 10:21:23 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args_separated_by_spaces(char **arg)
{
	while (*arg != NULL)
	{
		ft_putstr_fd(*arg, STDOUT_FILENO);
		if (*(arg + 1) != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg++;
	}
}

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
		i = 1;
		if (n_flag == ON)
			i++;
		print_args_separated_by_spaces(&sc->cmd_arg[i]);
		if (n_flag == OFF)
			ft_putstr_fd("\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	return (waitpid_n_get_exit_status(pid));
}
