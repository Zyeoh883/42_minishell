/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_ast_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 12:30:07 by Zyeoh             #+#    #+#             */
/*   Updated: 2024/05/27 22:34:21 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_subshell(t_token *token_root)
{
	while (token_root && token_root->type == WHITESPACE)
		token_root = token_root->next;
	if (token_root && token_root->type == OPEN_PARENT)
		return (1);
	return (0);
}

int	is_and_or(t_token *token)
{
	if ((token->type == AND || token->type == OR) && !is_in_parentheses(token))
		return (1);
	return (0);
}

int	is_pipe_token(t_token *token)
{
	if (token->type == PIPE && !is_in_parentheses(token))
		return (1);
	return (0);
}

int	is_command_token(t_token *token)
{
	if (!is_file_token(token) && token->type == WORDS)
		return (1);
	return (0);
}

int	count_content_in_tokens(t_token *token_root, int (*filter)(t_token *))
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

t_node	**ft_split_tokens(t_data *shell_data, t_token *token_root,
		int (*filter)(t_token *))
{
	t_node	**arr_nodes;
	t_token	*token;
	t_token	*temp;
	int		n;

	arr_nodes = ft_calloc(sizeof(t_node *), count_content_in_tokens(token_root,
				filter));
	if (!arr_nodes)
		perror_and_exit("malloc", EXIT_FAILURE);
	n = -1;
	token = token_root;
	while (token)
	{
		if (filter(token))
		{
			temp = token;
			token = token->next;
			token_remove(temp);
			token->prev->next = NULL;
			token->prev = NULL;
			arr_nodes[++n] = create_node(shell_data, token);
		}
		token = token->next;
	}
	return (arr_nodes);
}

t_redir	get_redir(t_token *token)
{
	t_token	*token_head;
	t_redir	redir;

	if (token->here_doc_file)
		redir.filename = ft_strdup(token->here_doc_file);
	else
		redir.filename = ft_strdup(token->value);
	if (!redir.filename)
		perror_and_exit("malloc", EXIT_FAILURE);
	token_head = token->prev;
	while (token_head && token_head->type == WHITESPACE)
		token_head = token_head->prev;
	redir.type = token_head->type - REDIR_OUT;
	return (redir);
}

t_redir	*extract_redir(t_token *token_root)
{
	t_token	*token;
	t_redir	*redir;
	int		redir_count;

	token = token_root;
	redir_count = count_content_in_tokens(token_root, is_file_token);
	if (redir_count == 0)
		return (NULL);
	redir = ft_calloc(sizeof(t_redir), redir_count + 1);
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
	cmd_count = count_content_in_tokens(token_root, is_command_token);
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
