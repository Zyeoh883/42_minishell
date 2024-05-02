/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 20:16:21 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/02 21:55:46 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (0);
	here_doc_filename = ft_strjoin(HERE_DOC_DIR, buffer);
	free(buffer);
	if (!here_doc_filename)
		return (0);
	fd = open(here_doc_filename, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(here_doc_filename);
		return (0);
	}
	token->here_doc_file = here_doc_filename;
	return (fd);
}

int	input_here_doc(t_token *token, int here_doc_id)
{
	char	*line;
	int		fd;
	int		limiter_len;

	fd = make_here_doc_file(token, here_doc_id);
	if (!fd)
		return (0);
    limiter_len = ft_strlen(token->value);
	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (line)
		{
			if (ft_strncmp(line, token->value, limiter_len) == 0 && *(line
					+ limiter_len) == '\n')
				break ;
			ft_putstr_fd(line, fd);
			free(line);
		}
	}
    return (1);
}
