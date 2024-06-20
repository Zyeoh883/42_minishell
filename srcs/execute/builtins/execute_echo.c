/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:59:30 by sting             #+#    #+#             */
/*   Updated: 2024/06/20 16:11:53 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! need to return int for failure?
// int	execute_echo(char **cmd_arg)
// {
// 	int	i;
// 	int	n_flag;

// 	printf(">>>>>BUILT_IN>>>>>\n");
// 	n_flag = OFF;
// 	if (cmd_arg[1] && ft_strcmp(cmd_arg[1], "-n") == 0)
// 		n_flag = ON;
// 	i = 1;
// 	if (n_flag == ON)
// 		i = 2;
// 	while (cmd_arg[i] != NULL)
// 	{
// 		ft_putstr_fd(cmd_arg[i], STDOUT_FILENO);
// 		if (cmd_arg[i + 1] != NULL)
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	if (n_flag == OFF)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	return (EXIT_SUCCESS);
// }

int	execute_echo(t_simple_command *sc) // ! NORM
{
	pid_t pid;
	int i;
	int n_flag;

	printf(">>>>>BUILT_IN>>>>>\n");
	pid = fork(); // fork
	if (pid < 0)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0) // Child
	{
		dup2_fdin_n_fdout(sc->fd);
		n_flag = OFF;
		if (sc->cmd_arg[1] && ft_strcmp(sc->cmd_arg[1], "-n") == 0)
			n_flag = ON;
		i = 1;
		if (n_flag == ON)
			i = 2;
		while (sc->cmd_arg[i] != NULL)
		{
			ft_putstr_fd(sc->cmd_arg[i], STDOUT_FILENO);
			if (sc->cmd_arg[i + 1] != NULL)
				ft_putstr_fd(" ", STDOUT_FILENO);
			i++;
		}
		if (n_flag == OFF)
			ft_putstr_fd("\n", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	return (waitpid_n_get_exit_status(pid));
}

// void	execute_echo(char **cmd_arg)
// {
// 	int	i;
// 	int	n_flag;

// 	n_flag = OFF;
// 	i = 1;
// 	while (cmd_arg[i] != NULL)
// 	{
// 		if ((i == 1 || (i > 1 && cmd_arg[i - 1][0] == '\0'))
// 			&& ft_strcmp(cmd_arg[i], "-n") == 0)
// 		{
// 			n_flag = ON;
// 			i++;
// 			continue ;
// 		}
// 		ft_putstr_fd(cmd_arg[i], STDOUT_FILENO);
// 		if (cmd_arg[i + 1] != NULL &&
// ! INSERT code in notion under "solution 2")
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	if (n_flag == OFF)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// }
