/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 16:57:53 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/09 19:58:19 by zyeoh            ###   ########.fr       */
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

void	ex_cmd(t_command *command)
{
	pid_t	pid;
	char	**PATH;
	char	**cmd;
	char	*cmd_lst;

	pid = fork();
	if (pid == 0)
	{
		PATH = ft_split(getenv("PATH"), ':');
		cmd = ft_split(command->str, ' ');
		cmd_lst = get_exec(PATH, cmd[0]);
		if (execve(cmd_lst, cmd, command->env) == -1) // ? Might free local before var before exit
		{
			ft_putstr_fd(cmd[0], 2);
			ft_putendl_fd(": Command not found", 2);
			exit(125);
		}
	}
}

// void	ex_pipe(t_pipe *pipe)
// {
// 	pid_t	pid;

// 	(void)pipe;
// 	piping();
// 	while (++n < pipe->n_nodes)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			coupling();
// 			execute(pipe->arr_nodes[n]);
// 		}
// 	}
// }

void	execute(t_node *node)
{
	if (node->type == COMMAND)
		ex_cmd(node->command);
	// else if (node->type == PIPE)
	// 	ex_pipe(node->pipe);
}

int	main(int ac, char **av, char **env)
{
	t_node *node;

	(void)ac;
	(void)av;
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	node->type = COMMAND;
	node->command = (t_command *)ft_calloc(1, sizeof(t_command));
	node->command->str = "ls -2";
	node->command->env = env;

	execute(node);
	// after parsing all the inputs and making AST

	// node->type = PIPE;
	// node->pipe->n_nodes = 2;
	// node->pipe->arr_nodes = malloc (sizeof(t_node *) * 2);
	// node->pipe->fd_in = STDIN_FILENO;
	// node->pipe->fd_out = STDOUT_FILENO;
	// next = &node->pipe->arr_nodes[0];

	// char *line;
	// line = readline("minishell> ");
	// ft_printf(line);
	// free(line);
	return (0);
}