/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:43:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/15 10:48:47 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_NODE_H
# define CREATE_NODE_H

# include "data_structs.h"
# include "minishell.h"

// t_node	tokenize_simple_command(char *input, char **env);

t_node	*create_node(t_nodetype type);
t_node	*create_command(char **env, char **cmd_arg);
t_node	*create_simple_command(char **env, char **files, t_node *command);

// piping

t_node	*create_pipe(t_node **nodes, int n_nodes);
int		build_pipes(t_pipe *pipe_node);
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);


#endif