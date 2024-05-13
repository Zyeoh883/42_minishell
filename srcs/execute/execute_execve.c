/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/13 15:17:05 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// search & construct valid executable path
char	*get_exec(char **cmd_path, char *cmd)
{
	char	*exec;
	char	*path_part;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (*cmd_path)
	{
		path_part = ft_strjoin(*cmd_path, "/");
		if_null_perror_n_exit(path_part, "ft_strjoin", EXIT_FAILURE);
		exec = ft_strjoin(path_part, cmd);
		if_null_perror_n_exit(exec, "ft_strjoin", EXIT_FAILURE);
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

// int	execute_execve(char **cmd_arg, char **my_env)
int	execute_execve(char **cmd_arg, t_var *var_lst)
{
	char	**path_arr;
	char	*exec_path;
	pid_t	pid;
	char *path_str;
	char **var_arr;

	var_arr = convert_var_lst_to_array(var_lst);	
	path_str = get_var("PATH", var_lst);
	if (path_str == NULL) // if user unset("PATH");
	{
		ft_putstr_fd(*cmd_arg, STDOUT_FILENO);
		ft_putendl_fd(": command not foundd", STDOUT_FILENO);
		free_str_arr(var_arr);
		return (ERROR_CMD_NOT_FOUND);
	}
	path_arr = ft_split(path_str, ':');
	if_null_perror_n_exit(path_arr, "ft_split", EXIT_FAILURE);
	exec_path = get_exec(path_arr, *cmd_arg);
	free_str_arr(path_arr);
	if (exec_path == NULL)
	{
		ft_putstr_fd(*cmd_arg, STDOUT_FILENO);
		ft_putendl_fd(": command not found", STDOUT_FILENO);
		free_str_arr(var_arr);
		free(exec_path);
		return (ERROR_CMD_NOT_FOUND);
	}
	pid = fork(); // fork
	if (pid < 0)
		perror_and_exit("fork", 1);
	else if (pid == 0) // Child
	{
		if (execve(exec_path, cmd_arg, var_arr) == -1)
		// ? Might free local before var before exit
		{
			ft_putstr_fd(*cmd_arg, STDOUT_FILENO);
			ft_putendl_fd(": command not found", STDOUT_FILENO);
			exit(ERROR_CMD_NOT_FOUND);
		}
	}
	// Parent
	printf("exec_path: %p\n", exec_path);
	free(exec_path);
	printf("var_arr: %p\n", var_arr);
	free_str_arr(var_arr);
	return (waitpid_n_get_exit_status(pid)); // ! return Exit status?
}
