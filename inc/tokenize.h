/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:57:34 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/25 18:59:22 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "minishell.h"

# define METACHARACTERS " '\"()|&<>"
// error code for `syntax error near unexpected token `1'` is 258

typedef enum e_tokentype
{
	QUOTESS,
	SUBSHELLS,
	AND_OR,
	PIPES,
	SIMPLE_COMMANDS,
}						t_tokentype;

typedef struct s_token
{
	char				*value;
	enum e_tokentype	type;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

// tokenize
t_token					*tokenize(char *line);

// utils
t_token					*str_to_token(char *start, int len);
void					free_tokens(t_token *token_root);
void					token_add_back(t_token **token_root, t_token *new);
t_token					*new_token(char *value);
int						is_metacharacter(char c);
int						is_in_quote_tokens(t_token *token);
t_token					*token_last(t_token *token);
t_token					*token_last_nonspace(t_token *token);

// random BS
int						is_valid_token(t_token *token);
void					set_isvalid_function_array(int is_meta,
							int (*isvalid_function_array[7])(t_token *));

#endif