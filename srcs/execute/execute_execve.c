/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/29 16:32:31 by sting            ###   ########.fr       */
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

int waitpid_n_get_exit_status(pid_t pid)
{
	int status;
	
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
	char **PATH;
	char *exec_path;
	pid_t pid;
	
	PATH = ft_split(my_getenv("PATH", my_env), ':');
	if (PATH == NULL)
		perror_and_exit("ft_split", 1);
	exec_path = get_exec(PATH, *cmd_arg);
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
	return (waitpid_n_get_exit_status(pid)); // ! return Exit status?                                                
}
