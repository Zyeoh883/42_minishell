/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/06/25 12:22:02 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_env(t_simple_command *sc)
{
	pid_t	pid;

	printf(">>>>>BUILT_IN>>>>>\n");
	pid = fork();
	if (pid < 0)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2_fdin_n_fdout(sc->fd);
		exit(print_env_var(sc->var_lst, ""));
	}
	return (waitpid_n_get_exit_status(pid));
}

int	execute_pwd(t_simple_command *sc)
{
	char	cwd[PATH_MAX];
	pid_t	pid;

	printf(">>>>>BUILT_IN>>>>>\n");
	pid = fork();
	if (pid < 0)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0)
	{
		dup2_fdin_n_fdout(sc->fd);
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror_and_exit("getcwd", EXIT_FAILURE);
		ft_putendl_fd(cwd, STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	return (waitpid_n_get_exit_status(pid));
}

int	execute_exit(t_simple_command *sc)
{
	(void)sc;
	exit(EXIT_SUCCESS);
}

int	execute_builtins(t_simple_command *sc)
{
	if (ft_strcmp(*sc->cmd_arg, "exit") == 0)
		return (execute_exit(sc));
	else if (ft_strcasecmp(*sc->cmd_arg, "echo") == 0)
		return (execute_echo(sc));
	else if (ft_strcasecmp(*sc->cmd_arg, "env") == 0)
		return (execute_env(sc));
	else if (ft_strcasecmp(*sc->cmd_arg, "pwd") == 0)
		return (execute_pwd(sc));
	else if (ft_strcmp(*sc->cmd_arg, "export") == 0)
		return (execute_export(sc));
	else if (ft_strcasecmp(*sc->cmd_arg, "cd") == 0)
		return (execute_cd(sc));
	else if (ft_strcmp(*sc->cmd_arg, "unset") == 0)
		return (execute_unset(sc));
	else if (is_assignment(*sc->cmd_arg))
		return (execute_assignment(sc));
	else
		return (NOT_BUILTIN);
}
