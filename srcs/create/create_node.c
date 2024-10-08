/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:44:49 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/30 15:27:10 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_linker(t_nodetype type, t_var *env_var)
{
	t_node	*node;

	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
	{
		perror("Failed to create linker node");
		return (NULL);
	}
	node->var_lst = env_var;
	node->type = type;
	return (node);
}

// t_node	*create_pipe(t_node **nodes, int n_nodes)
// {
// 	t_node *node;

// 	node = create_linker(PIPE);
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
