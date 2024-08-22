/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:02:37 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 11:03:21 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_instances(t_token *token_root, int (*filter)(t_token *))
{
	int	count;

	count = 0;
	while (token_root)
	{
		if (filter(token_root))
			count++;
		token_root = token_root->next;
	}
	return (count);
}

t_node	**ft_split_tokens(t_data *shell_data, t_token *token,
		int (*filter)(t_token *))
{
	t_node	**arr_nodes;
	t_token	*token_head;
	int		n;

	arr_nodes = ft_calloc(sizeof(t_node *), token_instances(token, filter) + 2);
	if (!arr_nodes)
		perror_and_exit("malloc", EXIT_FAILURE);
	n = -1;
	token_head = token;
	while (token_head)
	{
		if (filter(token_head))
		{
			token_head = token_head->next;
			token_remove(token_head->prev);
			token_head->prev->next = NULL;
			token_head->prev = NULL;
			arr_nodes[++n] = create_node(shell_data, token);
			token = token_head;
		}
		else
			token_head = token_head->next;
	}
	arr_nodes[++n] = create_node(shell_data, token);
	return (arr_nodes);
}

t_redir	*get_redir(t_token *token)
{
	t_token	*token_head;
	t_redir	*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		perror_and_exit("malloc", EXIT_FAILURE);
	if (token->here_doc_file)
		redir->filename = ft_strdup(token->here_doc_file);
	else
		redir->filename = ft_strdup(token->value);
	if (!redir->filename)
		perror_and_exit("malloc", EXIT_FAILURE);
	token_head = token->prev;
	while (token_head && token_head->type == WHITESPACE)
		token_head = token_head->prev;
	redir->type = token_head->type - REDIR_OUT;
	return (redir);
}

t_redir	**extract_redir(t_token *token_root)
{
	t_token	*token;
	t_redir	**redir;
	int		redir_count;

	token = token_root;
	redir_count = token_instances(token_root, is_file_token);
	if (redir_count == 0)
		return (NULL);
	redir = ft_calloc(sizeof(t_redir *), redir_count + 1);
	if (!redir)
		perror_and_exit("malloc", EXIT_FAILURE);
	redir_count = 0;
	token = token_root;
	while (token)
	{
		if (is_file_token(token))
		{
			redir[redir_count] = get_redir(token);
			redir_count++;
		}
		token = token->next;
	}
	return (redir);
}

char	**extract_commands(t_token *token_root)
{
	t_token	*token;
	char	**commands;
	int		cmd_count;

	token = token_root;
	cmd_count = token_instances(token_root, is_command_token);
	if (cmd_count == 0)
		return (NULL);
	commands = ft_calloc(sizeof(char *), cmd_count + 1);
	if (!commands)
		perror_and_exit("malloc", EXIT_FAILURE);
	cmd_count = 0;
	token = token_root;
	while (token)
	{
		if (!is_file_token(token) && token->type == WORDS)
		{
			commands[cmd_count] = ft_strdup(token->value);
			if (!commands[cmd_count])
				perror_and_exit("malloc", EXIT_FAILURE);
			cmd_count++;
		}
		token = token->next;
	}
	return (commands);
}
