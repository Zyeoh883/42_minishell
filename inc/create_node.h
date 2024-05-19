/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:43:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/19 15:14:17 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_NODE_H
# define CREATE_NODE_H

# include "data_structs.h"

// t_node	tokenize_simple_command(char *input, char **env);

t_node	*create_node(t_nodetype type);
t_node	*create_command(char **env, char **cmd);
t_node	*create_simple_command(char **env, t_redir *redir, char **cmd, int is_built_in);

// piping

t_node	*create_pipe(t_node **nodes, int n_nodes);
int		build_pipes(t_pipe *pipe_node);
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);


#endif