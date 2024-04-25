/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_execve.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/04/25 16:59:24 by sting            ###   ########.fr       */
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
	int exit_status;
	
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_status = WEXITSTATUS(status);
		if (exit_status == 0)
			return (0);
		return (exit_status);
	}
	else
	{
	 	// Child process terminated due to a signal (handle this case)
		return (SIGNALINT);
	}
}

int	execute_execve(char **cmd_arg, char **env)
{
	char **PATH;
	char *cmd_lst;
	pid_t pid;

	PATH = ft_split(getenv("PATH"), ':');
	cmd_lst = get_exec(PATH, *cmd_arg);

	pid = fork();
	if (pid < 0)
	{
		// error handling
		return (FAIL);
	}
	else if (pid == 0) // Child
	{
		if (execve(cmd_lst, cmd_arg, env) == -1)
		// ? Might free local before var before exit
		{
			ft_putstr_fd(*cmd_arg, 2);
			ft_putendl_fd(": command not found", 2);
			exit(ERROR_CMD_NOT_FOUND);
		}
	}
	// Parent
	if (waitpid_n_get_exit_status(pid) == 0)
		return (SUCCESS);    
	return (FAIL);                                                
}