/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/06/10 10:18:33 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// search & construct valid executable path
char	*get_exec(char **cmd_path, char *cmd)
{
	char	*exec;
	char	*path_part;

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

	waitpid(pid, &status, 0); // ! issue here (program hang)
	if (WIFEXITED(status))
		return (WEXITSTATUS(status)); // return exit status
	else
	{
		// TODO: Child process terminated due to a signal (handle this case)
		return (SIGNALINT);
	}
}


int	check_file_status(char *arg)
{
	if (access(arg, F_OK != 0))
		return (perror_and_return(arg, ERR_NO_SUCH_FILE_OR_DIR));
	if (is_directory(arg))
		return (print_custom_err_n_return(arg, "", ": is a directory",
				ERR_CMD_NOT_EXECUTABLE));
	if (access(arg, X_OK) != 0)
		return (perror_and_return(arg, ERR_CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}

// - if '/' is present in 1st cmd, program does checks assuming it's a file/dir
char	*find_exec_path(char **cmd_arg, t_var *var_lst)
{
	char	*path_str;
	char	*exec_path;
	int		status;
	char	**path_arr;

	path_str = get_var_value("PATH", var_lst);
	if (ft_strchr(*cmd_arg, '/') != NULL || path_str == NULL)
	{
		status = check_file_status(*cmd_arg);
		if (status != EXIT_SUCCESS)
			exit(status);
		exec_path = ft_strdup(*cmd_arg);
		if_null_perror_n_exit(exec_path, "ft_strdup", EXIT_FAILURE);
	}
	else // check with PATH
	{
		path_arr = ft_split(path_str, ':');
		if_null_perror_n_exit(path_arr, "ft_split", EXIT_FAILURE);
		exec_path = get_exec(path_arr, *cmd_arg);
		free_str_arr(path_arr);
		if (exec_path == NULL)
			exit(print_custom_err_n_return(*cmd_arg, "", ": command not found",
					ERR_CMD_NOT_FOUND));
	}
	return (exec_path);
}


// int	execute_execve(t_simple_command *sc)
// {
// 	char	*exec_path;
// 	pid_t	pid;
// 	char	**var_arr;

// 	pid = fork(); // fork
// 	if (pid < 0)
// 		perror_and_exit("fork", EXIT_FAILURE);
// 	else if (pid == 0) // Child
// 	{
// 		// TODO: open_file_n_dup2
// 		exec_path = find_exec_path(sc->cmd_arg, sc->var_lst);
// 		var_arr = convert_var_lst_to_array(sc->var_lst);
// 		if (execve(exec_path, sc->cmd_arg, var_arr) == -1)
// 		{
// 			free(exec_path);
// 			free(var_arr);
// 			exit(print_custom_err_n_return(*sc->cmd_arg, "",
// 					": command not founddd", ERR_CMD_NOT_FOUND));
// 		}
// 	}
// 	return (waitpid_n_get_exit_status(pid));
// }

int	execute_execve(t_simple_command *sc)
{
	char	*exec_path;
	pid_t	pid;
	char	**var_arr;

	pid = fork(); // fork
	if (pid < 0)
		perror_and_exit("fork", EXIT_FAILURE);
	else if (pid == 0) // Child
	{
		// TODO: open_file_n_dup2
		// if (setup_redir(sc->redir) == EXIT_FAILURE)
		// 	exit(EXIT_FAILURE);
		dup2_fdin_n_fdout(sc->fd);
		exec_path = find_exec_path(sc->cmd_arg, sc->var_lst);
		var_arr = convert_var_lst_to_array(sc->var_lst);
		if (execve(exec_path, sc->cmd_arg, var_arr) == -1)
		{
			free(exec_path);
			free(var_arr);
			exit(print_custom_err_n_return(*sc->cmd_arg, "",
					": command not founddd", ERR_CMD_NOT_FOUND));
		}
	}
	return (waitpid_n_get_exit_status(pid));
}