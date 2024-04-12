/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/12 22:32:48 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_node *node)
{
	if (node->type == COMMAND)
		ex_cmd(node->command);
	else if (node->type == REDIRECTION_IN)
		ex_cmd(node->command);
	// else if (node->type == PIPE)
	// 	ex_pipe(node->pipe);
}

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

void	ex_cmd(t_command *command)
{
	char	**PATH;
	char	**cmd;
	char	*cmd_lst;

	PATH = ft_split(getenv("PATH"), ':');
	cmd = ft_split(command->cmd, ' ');
	cmd_lst = get_exec(PATH, cmd[0]);
	if (execve(cmd_lst, cmd, command->env) == -1)
	// ? Might free local before var before exit
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(": Command not found", 2);
		exit(125);
	}
}

void	ex_redir_in(t_redir_in *redir_in) // TODO chnage this to general redirect
{
	int n;
	int fd;

	n = -1;
	while (redir_in->files[++n])
	{
		fd = open(redir_in->files[n], O_RDONLY);
		if (fd < 0)
		{
			perror("open"); // TODO change error message to match BASH error msg
			return ;
		}
		close(fd);
	}
	fd = open(redir_in->files[n], O_RDONLY);

}
