/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:44:49 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/12 21:06:44 by zyeoh            ###   ########.fr       */
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

t_node	*create_command(char **env, char *cmd)
{
	t_node	*node;

	node = create_node(COMMAND);
	if (!node)
		exit(125);
	node->command = (t_command *)ft_calloc(1, sizeof(t_command));
	if (!node->command)
	{
		perror("Failed to create command node");
		free(node);
		exit(125);
	}
	node->command->cmd = cmd;
	node->command->env = env;
	return (node);
}

t_node	*create_redir_in(char **env, char **files, t_node *command)
{
	t_node	*node;

	node = create_node(REDIRECTION_IN);
	if (!node)
		exit(125);
	node->redir_in = (t_redir_in *)ft_calloc(1, sizeof(t_redir_in));
	if (!node->redir_in)
	{
		perror("Failed to create redir_in node");
		free(node);
		exit(125);
	}
	node->redir_in->cmd = command;
	return (node);
}

// fd = open(files[n_files], O_RDONLY);
// 		if (fd < 0)
// 		{
// 			perror("Failed to open file");
// 			return (NULL);
// 		}