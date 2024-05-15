/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:44:49 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/15 16:42:32 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_node(t_nodetype type)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
	{
		perror("Failed to create linker node");
		return (NULL);
	}
	node->type = type;
	return (node);
}

t_node	*create_simple_command(char **env, t_redir *redir, char **cmd, int is_built_in)
{
	t_node	*node;

	node = create_node(SIMPLE_COMMAND);
	if (!node)
		perror_and_exit("Failed to create simple_command linker", 125);
	node->simple_command = (t_simple_command *)ft_calloc(1,
			sizeof(t_simple_command));
	if (!node->simple_command)
	{
		free(node);
		perror_and_exit("Failed to create simple_command node", 125);
	}
	(void)  env;
	node->simple_command->redir = redir;
	(void) cmd;
	node->simple_command->is_built_in = is_built_in;
	return (node);
}

t_node	*create_pipe(t_node **nodes, int n_nodes)
{
	t_node *node;

	node = create_node(PIPE);
	if (!node)
		exit(125);
	node->pipe = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!node->pipe)
	{
		perror("Failed to create pipe node");
		free(node);
		exit(125);
	}
	node->pipe->arr_nodes = nodes;
	node->pipe->n_nodes = n_nodes;
	if (!build_pipes(node->pipe))
	{
		free(node);
		exit(125);
	}
	return (node);
}
