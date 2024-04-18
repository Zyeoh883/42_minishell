/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:45:53 by sting             #+#    #+#             */
/*   Updated: 2024/04/18 15:07:49 by sting            ###   ########.fr       */
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
void	execute_cmd(t_command *command)
{
	char	**PATH;
	char	**cmd;
	char	*cmd_lst;

	PATH = ft_split(getenv("PATH"), ':');
	cmd = ft_split(command->str, ' ');
	cmd_lst = get_exec(PATH, cmd[0]);
	if (execve(cmd_lst, cmd, command->env) == -1)
	// ? Might free local before var before exit
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": Command not found", 2);
		exit(125);
	}
}

void	execute(t_node *node)
{
	if (node->type == COMMAND)
		execute_cmd(node->command);
	// else if (node->type == REDIRECTION_IN)
	// 	execute_cmd(node->command);
	// else if (node->type == PIPE)
	// 	ex_pipe(node->pipe);
}

