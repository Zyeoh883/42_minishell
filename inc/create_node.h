/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:43:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 13:02:19 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_NODE_H
# define CREATE_NODE_H

# include "minishell.h"

typedef struct s_data				t_data;
typedef struct s_var				t_var;
typedef struct s_redir				t_redir;
typedef struct s_token				t_token;
typedef struct s_node				t_node;
typedef struct s_pipe				t_pipe;
typedef struct s_subshell			t_subshell;
typedef struct s_and_or				t_and_or;
typedef struct s_simple_command		t_simple_command;

t_redir					**extract_redir(t_token *token_root);
char					**extract_commands(t_token *token_root);
t_token					*find_top_closing_parent(t_token *token);

// t_node	tokenize_simple_command(char *input, char **env);

t_node					**ft_split_tokens(t_data *shell_data, t_token *token,
							int (*filter)(t_token *));
int						token_instances(t_token *token,
							int (*filter)(t_token *));
int						is_subshell(t_token *token_root);
int						is_and_or(t_token *token);
int						is_pipe_token(t_token *token);
int						is_command_token(t_token *token);

t_node					*create_ast(t_data *shell_data);
t_node					*create_node(t_data *shell_data, t_token *token);
t_node					*create_subshell(t_data *shell_data, t_token *token);
t_node					*create_and_or(t_data *shell_data, t_token *token);
t_node					*create_pipe(t_data *shell_data, t_token *token);
t_node					*create_linker(t_nodetype type, t_var *env_var);
t_node					*create_simple_command(t_data *shell_data,
							t_token *token);

// testing
void					print_ast(t_node *node, int depth);

// free ast
void					free_redir(t_redir **redir);
void					free_and_or(t_and_or *and_or);
void					free_pipe(t_pipe *pipe);
void					free_subshell(t_subshell *subshell);
void					free_simple_command(t_simple_command *sc);
void					free_ast(t_node *node);

#endif