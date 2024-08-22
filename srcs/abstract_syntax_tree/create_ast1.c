/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:27:12 by Zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 11:05:01 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_subshell(t_data *shell_data, t_token *token)
{
	t_token	*token_head;
	t_node	*node;

	node = create_linker(SUBSHELL, shell_data->var_lst);
	if (!node)
		perror_and_exit("Failed to linker", 125);
	node->subshell = ft_calloc(1, sizeof(t_subshell));
	if (!node->subshell)
		perror_and_exit("Failed to create subshell node", 125);
	token_head = find_top_closing_parent(token);
	if (token_head)
	{
		node->subshell->redir = extract_redir(token_head->next);
		token_head->prev->next = NULL;
		free_tokens(token_head);
	}
	while (token->type != OPEN_PARENT)
	{
		token = token->next;
		token_remove(token->prev);
	}
	token = token->next;
	token_remove(token->prev);
	node->subshell->node = create_node(shell_data, token);
	return (node);
}

t_node	*create_and_or(t_data *shell_data, t_token *token)
{
	t_token	*token_head;
	t_node	*node;
	int		n;

	node = create_linker(AND_OR, shell_data->var_lst);
	if (!node)
		perror_and_exit("Failed to create linker", 125);
	node->pipe = ft_calloc(1, sizeof(t_and_or));
	if (!node->pipe)
		perror_and_exit("Failed to create pipe node", 125);
	n = token_instances(token, is_and_or);
	node->and_or->operators = ft_calloc(n + 1, sizeof(int));
	if (!node->and_or->operators)
		perror_and_exit("Failed to create operators", 125);
	n = -1;
	token_head = token;
	while (token_head)
	{
		if (is_and_or(token_head))
			node->and_or->operators[++n] = token_head->type;
		token_head = token_head->next;
	}
	node->and_or->arr_nodes = ft_split_tokens(shell_data, token, is_and_or);
	return (node);
}

t_node	*create_pipe(t_data *shell_data, t_token *token)
{
	t_node	*node;

	node = create_linker(PIPE, shell_data->var_lst);
	if (!node)
		perror_and_exit("Failed to create linker", 125);
	node->pipe = ft_calloc(1, sizeof(t_pipe));
	if (!node->pipe)
		perror_and_exit("Failed to create pipe node", 125);
	node->pipe->n_nodes = token_instances(token, is_pipe_token) + 1;
	node->pipe->n_nodes = token_instances(token, is_pipe_token) + 1;
	node->pipe->arr_nodes = ft_split_tokens(shell_data, token, is_pipe_token);
	return (node);
}

t_node	*create_simple_command(t_data *shell_data, t_token *token)
{
	t_node	*node;

	node = create_linker(SIMPLE_COMMAND, shell_data->var_lst);
	if (!node)
		perror_and_exit("Failed to linker", 125);
	node->simple_command = ft_calloc(1, sizeof(t_simple_command));
	if (!node->simple_command)
		perror_and_exit("Failed to create simple_command node", 125);
	node->simple_command->var_lst = shell_data->var_lst;
	node->simple_command->redir = extract_redir(token);
	node->simple_command->cmd_arg = extract_commands(token);
	free_tokens(token);
	return (node);
}

t_node	*create_ast(t_data *shell_data)
{
	t_node	*result;

	if (g_signal == SIGINT)
		return (NULL);
	result = create_node(shell_data, shell_data->token_root);
	return (result);
}

// commands = extract_commands(shell_data->token_root);
// redir = extract_redir(shell_data->token_root);
// print_str_arr(commands, "commands");
// while (redir && redir->filename)
// {
// 	printf("redir->filename: %s && type: %d\n", redir->filename, redir->type);
// 	redir++;
// }