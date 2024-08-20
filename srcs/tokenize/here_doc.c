/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:16:21 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/20 16:58:10 by zyeoh            ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

int	is_here_doc(t_token *token)
{
	if (!token || !token->prev || token->type != WORDS)
		return (0);
	token = token->prev;
	while (token && token->type == WHITESPACE)
		token = token->prev;
	if (token && token->type == REDIR_HEREDOC)
		return (1);
	return (0);
}

int	make_here_doc_file(t_token *token, int here_doc_id)
{
	char	*here_doc_filename;
	char	*buffer;
	int		fd;

	buffer = ft_itoa(here_doc_id);
	if (!buffer)
		perror_and_exit("malloc failed", EXIT_FAILURE);
	here_doc_filename = ft_strjoin(HERE_DOC_DIR, buffer);
	free(buffer);
	if (!here_doc_filename)
		perror_and_exit("malloc failed", EXIT_FAILURE);
	fd = open(here_doc_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(here_doc_filename);
		return (0);
	}
	token->here_doc_file = here_doc_filename;
	return (fd);
}

char	*trim_limiter(char *token_limiter)
{
	char	*trimmed;

	if (token_limiter[0] == '\'' || token_limiter[0] == '\"')
	{
		trimmed = ft_substr(token_limiter, 1, ft_strlen(token_limiter) - 2);
		if (!trimmed)
			perror_and_exit("malloc failed", EXIT_FAILURE);
		return (trimmed);
	}
	trimmed = ft_substr(token_limiter, 0, ft_strlen(token_limiter));
	if (!trimmed)
		perror_and_exit("malloc failed", EXIT_FAILURE);
	return (trimmed);
}

int	input_here_doc(t_token *token, int here_doc_id)
{
	char	*input;
	int		fd;
	char	*limiter;
	int		limiter_len;

	fd = make_here_doc_file(token, here_doc_id);
	if (!fd)
		return (0);
	limiter = trim_limiter(token->value);
	limiter_len = ft_strlen(limiter);
	while (1)
	{
		input = readline("> ");
		if (!input || (ft_strcmp(input, limiter) == 0
				&& limiter_len == ft_strlen(input)) || g_signal == SIGINT)
			break ;
		ft_putendl_fd(input, fd);
		free(input);
	}
	free(input);
	free(limiter);
	close(fd);
	if (g_signal == SIGINT)
		return (0);
	return (1);
}
