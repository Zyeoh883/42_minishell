/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/06 16:38:41 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exec(char **cmd_path, char *cmd)
{
	char	*exec;
	char	*path_part;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (*cmd_path)
	{
		path_part = ft_strjoin(*cmd_path, "/");
		exec = ft_strjoin(path_part, cmd);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
		cmd_path++;
	}
	return (NULL);
}

int	waitpid_n_get_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // return exit status
	else
	{
		// TODO: Child process terminated due to a signal (handle this case)
		return (SIGNALINT);
	}
}

int	execute_execve(char **cmd_arg, char **my_env)
{
	char	**path_arr;
	char	*exec_path;
	pid_t	pid;
	char *path_str;

	path_str = my_getenv("PATH", my_env);
	if (path_str == NULL) // if user unset("PATH");
	{
		ft_putstr_fd(*cmd_arg, 2);
		ft_putendl_fd(": command not found", 2);
		return (ERROR_CMD_NOT_FOUND);
	}
	path_arr = ft_split(path_str, ':');
	if (path_arr == NULL)
		perror_and_exit("ft_split", 1);
	exec_path = get_exec(path_arr, *cmd_arg);
	if (exec_path == NULL)
		perror_and_exit("get_exec", EXIT_FAILURE);
	pid = fork(); // fork
	if (pid < 0)
		perror_and_exit("fork", 1);
	else if (pid == 0) // Child
	{
		if (execve(exec_path, cmd_arg, my_env) == -1)
		// ? Might free local before var before exit
		{
			ft_putstr_fd(*cmd_arg, 2);
			ft_putendl_fd(": command not found", 2);
			exit(ERROR_CMD_NOT_FOUND);
		}
	}
	// Parent
	free_str_arr(path_arr);
	free(exec_path);
	return (waitpid_n_get_exit_status(pid)); // ! return Exit status?
}
