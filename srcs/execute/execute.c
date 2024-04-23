/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 15:01:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/23 07:45:54 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_node *node) // TODO add an empty parameter check
{
	if (node->type == SIMPLE_COMMAND)
		ex_simple_command(node->simple_command);
	else if (node->type == PIPE)
		ex_pipe(node->pipe);
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

// void	ex_cmd(t_command *command)
// {
// 	char	**PATH;
// 	char	*cmd_lst;

// 	PATH = ft_split(getenv("PATH"), ':');
// 	cmd_lst = get_exec(PATH, *command->cmd);
// 	if (execve(cmd_lst, command->cmd, command->env) == -1)
// 	// ? Might free local before var before exit
// 	{
// 		ft_putstr_fd(*command->cmd, 2);
// 		ft_putendl_fd(": Command not found", 2);
// 		exit(125);
// 	}
// }

void	ex_simple_command(t_simple_command *simple_command) // TODO add the redirect functionality
{
	char	**PATH;
	char	*cmd_lst;

	PATH = ft_split(getenv("PATH"), ':');
	cmd_lst = get_exec(PATH, *simple_command->cmd);
	if (execve(cmd_lst, simple_command->cmd, simple_command->env) == -1)
	// ? Might free local before var before exit
	{
		ft_putstr_fd(*simple_command->cmd, 2);
		ft_putendl_fd(": Command not found", 2);
		exit(125);
	}

	// if (simple_command->cmd->type == COMMAND)
	// 	execute(simple_command->cmd);
	// int n;
	// int fd;

	// n = -1;
	// while (redir_in->files[++n])
	// {
	// 	fd = open(redir_in->files[n], O_RDONLY);
	// 	if (fd < 0)
	// 	{
	// 		perror("open"); // TODO change error message to match BASH error msg
	// 		return ;
	// 	}
	// 	close(fd);
	// }
	// fd = open(redir_in->files[n], O_RDONLY);
}

void	ex_pipe(t_pipe *pipe)
{
	pid_t pid;
	int n;

	n = -1;
	while (++n < pipe->n_nodes)
	{
		pid = fork();
		if (pid == 0)
		{
			coupling(pipe, n);
			close_pipes(pipe);
			execute(pipe->arr_nodes[n]);
		}
	}
}
