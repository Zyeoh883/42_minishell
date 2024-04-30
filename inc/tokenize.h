/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Zyeoh <yeohzishen2002@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:57:34 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/30 17:11:18 by Zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "minishell.h"

# define METACHARACTERS " '\"()|&<>"
# define OPERAND " '\"()|&<>"
// error code for `syntax error near unexpected token `1'` is 258

# define WORDS 0
# define SPACE 1
# define AMPERSAND 2

# define REDIR_OUT 3
# define REDIR_IN 4
# define REDIR_APPEND 5
# define REDIR_HEREDOC 6
# define PIPE 7
# define AND 8
# define OR 9
# define OPEN_PARENT 10
# define CLOSED_PARENT 11

typedef struct s_token
{
	char			*value;
	int				open_end;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// tokenize
t_token				*tokenize(char *line);
void				format_tokens(t_token *token_root);

// utils
t_token				*str_to_token(char *start, int len);
void				free_tokens(t_token *token_root);
void				token_add_back(t_token **token_root, t_token *new);
t_token				*new_token(char *value);
t_token				*token_last(t_token *token);
t_token				*token_last_nonspace(t_token *token);
void				token_remove(t_token *token);
void	print_tokens(t_token *token);

int					token_combine_wnext(t_token *token);

// validattions
int					is_metacharacter(char c);
int					is_operand(char c);
int					is_in_quote_tokens(t_token *token);
int					is_valid_multi_operand(t_token *token);
int					is_valid_redir_file(t_token *token);
int					is_valid_edgecase_digit_redir(t_token *token);
int					is_valid_closed_parenthesis(t_token *token);
int					is_valid_parenthesis_content(t_token *token);
int					is_valid_parenthesis_position(t_token *token);
int					is_valid_operand_position(t_token *token);
int					is_valid_special_character(t_token *token);

// validation utils
int					is_file_token(t_token *token);

// random BS
int					is_valid_token(t_token *token);
void				set_isvalid_function_array(int is_meta,
						int (*isvalid_function_array[10])(t_token *));

#endif