/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:43:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/29 15:39:53 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_NODE_H
# define CREATE_NODE_H

# include "minishell.h"

typedef struct s_token	t_token;
typedef struct s_data	t_data;

t_redir					*extract_redir(t_token *token_root);
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
t_node					*create_linker(t_nodetype type);
t_node					*create_simple_command(t_data *shell_data,
							t_token *token);

// piping
int						build_pipes(t_pipe *pipe_node);
void					coupling(t_pipe *pipe_node, int n);
void					close_pipes(t_pipe *pipe_node);

// testing
void					print_ast(t_node *node, int depth);

#endif