/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:42:10 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/05 21:10:54 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void unlink_here_doc_files(t_token *token_root)
{
	t_token	*tmp;

	while (token_root)
	{
		tmp = token_root;
		token_root = token_root->next;
		if (tmp->here_doc_file)
		{
			unlink(tmp->here_doc_file);
		}
	}	
}

//unlink_here_doc_files(token_root);

void	free_tokens(t_token *token_root)
{
	t_token	*tmp;

	while (token_root)
	{
		tmp = token_root;
		token_root = token_root->next;
		if (tmp->here_doc_file)
			free(tmp->here_doc_file);
		free(tmp->value);
		free(tmp);
	}
}

void	token_add_back(t_token **token_root, t_token *new)
{
	t_token	*head;

	if (!*token_root)
	{
		*token_root = new;
		return ;
	}
	head = *token_root;
	while (head->next)
		head = head->next;
	head->next = new;
	new->prev = head;
}

t_token	*new_token(char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	return (token);
}

t_token	*token_last(t_token *token)
{
	while (token->next)
		token = token->next;
	return (token);
}

t_token	*token_last_nonspace(t_token *token)
{
	t_token	*head;

	head = token;
	while (head)
	{
		if (*head->value != ' ')
			token = head;
		head = head->next;
	}
	return (token);
}

void token_remove(t_token *token)
{
	t_token *prev;
	t_token *next;
	
	if (!token)
		return;
	prev = token->prev;
	next = token->next;
	free(token->value);
	free(token);
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
}

void	token_combine_wnext(t_token *token)
{
	char *new_value;

	if (!token || !token->next)
		return ;
	new_value = ft_strjoin(token->value, token->next->value);
	if (!new_value)
		perror_and_exit("malloc error", EXIT_FAILURE);
	free(token->value);
	token->value = new_value;
	token_remove(token->next);
}

int is_token_open_ended(t_token *token_root)
{
	t_token *last;

	if (!token_root)
		return (0);
	last = token_last_nonspace(token_root);
	if (last->type == OPEN_PARENT)
		return (1);
	if (last->open_end || is_in_parentheses(last))
		return (1);
	if (PIPES<= last->type && last->type <= OR)
		return (1);
	return (0);
}

//

// int	main(int argc, char **argv, char **env)
// {
// 	char	*input;
// 	char	*line;
// 	char	**my_env;
// 	t_token	*token_root;
// 	t_token	*buffer;

// 	(void)argc;
// 	(void)argv;
// 	// pid_t	pid;
// 	// char	**cmd;
// 	if (access("/tmp", F_OK) == -1)
// 	{
// 		printf("minishell: /tmp: No such file or directory\n");
// 		return (1);
// 	}
// 	// my_env = create_env_copy(env);
// 	while (handle_readline(mode , input))
// 	{
// 		token_root = tokenize(input);
// 		free(input);
// 		if (!token_root)
// 			break ;
// 		print_tokens(token_root);
// 		mode = 0;
// 		if (token_root && is_token_open_ended(token_root))
// 			mode = 1; //open_end
// 		{
// 			input = handle_readline("> ");
// 			if (!input)
// 				break ;
// 			buffer = tokenize(input);
// 			free(input);
// 			if (!buffer)
// 				break ;
// 			token_add_back(&token_root, buffer);
// 			free(input);
// 			print_tokens(token_root);
// 		}
// 		add_history(input); // working history
// 		free_tokens(token_root);
// 	}
// 	free_tokens(token_root);
// 	// free_str_arr(my_env);
// 	return (0);
// }





// 	while (1)
// 	{
// 		input = handle_readline("minishell$ ");
// 		if (!input)
// 			break ;
// 		token_root = tokenize(input);
// 		free(input);
// 		if (!token_root)
// 			break ;
// 		print_tokens(token_root);
// 		while (token_root && is_token_open_ended(token_root))
// 		{
// 			input = handle_readline("> ");
// 			if (!input)
// 				break ;
// 			buffer = tokenize(input);
// 			free(input);
// 			if (!buffer)
// 				break ;
// 			token_add_back(&token_root, buffer);
// 			free(input);
// 			print_tokens(token_root);
// 		}
// 		add_history(input); // working history
// 		free_tokens(token_root);
// 		// cmd = ft_split(input, ' ');
// 		// t_node	*node = create_simple_command(env, NULL, cmd, 0);
// 		// TODO free node after
// 		// pid = fork(); // fork for each execution
// 		// if (pid == 0)
// 		// {
// 		// 	(void)node;
// 		// 	exit(0);
// 		// 	// execute(node);
// 		// }
// 		// else
// 		// {
// 		// 	free_split(cmd);
// 		// 	free(input);
// 		// 	waitpid(pid, NULL, 0);
// 		// }
// 	}
// 	free_tokens(token_root);
// 	// free_str_arr(my_env);
// 	return (0);
// }