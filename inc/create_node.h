/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:43:42 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/12 20:57:26 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_NODE_H
# define CREATE_NODE_H

# include "data_structs.h"
# include "minishell.h"

t_node	*create_node(t_nodetype type);
t_node	*create_command(char **env, char *cmd);
t_node	*create_redir_in(char **env, char **files, t_node *command);

#endif