/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:44:49 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/15 10:48:47 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_nodetype type, t_var *var_lst)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
	{
		perror("Failed to create linker node");
		return (NULL);
	}
	node->type = type;
	node->var_lst = var_lst;
	return (node);
}

// t_node	*create_command(char **env, char **cmd_arg)
// {
// 	t_node	*node;

// 	node = create_node(COMMAND);
// 	if (!node)
// 		exit(125);
// 	node->command = (t_command *)ft_calloc(1, sizeof(t_command));
// 	if (!node->command)
// 	{
// 		perror("Failed to create command node");
// 		free(node);
// 		exit(125);
// 	}
// 	node->command->cmd_arg = cmd_arg;
// 	node->command->env = env;
// 	return (node);
// }

t_node	*create_simple_command(t_var *var_lst, char **cmd_arg)
{
	t_node	*node;

	node = create_node(SIMPLE_COMMAND, var_lst);
	if (!node)
		exit(125);
	node->simple_command = (t_simple_command *)ft_calloc(1, sizeof(t_simple_command));
	if (!node->simple_command)
	{
		perror("Failed to create simple_command node");
		free(node);
		exit(125);
	}
	node->simple_command->cmd_arg = cmd_arg;
	node->simple_command->var_lst = var_lst;
	node->simple_command->is_built_in = 0;
	return (node);
}

// t_node	*create_simple_command(char **env, char **files, t_node *command)
// {
// 	t_node	*node;

// 	(void)files;
// 	(void)env;
// 	node = create_node(SIMPLE_COMMAND);
// 	if (!node)
// 		exit(125);
// 	node->simple_command = (t_simple_command *)ft_calloc(1,
// 			sizeof(t_simple_command));
// 	if (!node->simple_command)
// 	{
// 		perror("Failed to create redir_in node");
// 		free(node);
// 		exit(125);
// 	}
// 	node->simple_command->cmd_arg = command;
// 	return (node);
// }

// t_node	*create_pipe(t_node **nodes, int n_nodes)
// {
// 	t_node *node;

// 	node = create_node(PIPE);
// 	if (!node)
// 		exit(125);
// 	node->pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
// 	if (!node->pipe)
// 	{
// 		perror("Failed to create pipe node");
// 		free(node);
// 		exit(125);
// 	}
// 	node->pipe->arr_nodes = nodes;
// 	node->pipe->n_nodes = n_nodes;
// 	if (!build_pipes(node->pipe))
// 	{
// 		free(node);
// 		exit(125);
// 	}
// 	return (node);
// }
