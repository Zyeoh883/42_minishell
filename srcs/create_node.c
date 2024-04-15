/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:33:21 by sting             #+#    #+#             */
/*   Updated: 2024/04/15 16:35:08 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include ".././inc/minishell.h"

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

t_node	*create_command(char **env, char *str)
{
	t_node	*node;

	node = create_node(COMMAND);
	if (!node)
		exit(125);
	node->command = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!node->command)
	{
		perror("Failed to create command node");
		free(node);
		exit(125);
	}
	node->command->str = str;
	node->command->env = env;
	return (node);
}