/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:17:35 by sting             #+#    #+#             */
/*   Updated: 2024/05/29 18:26:03 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

// * EXECUTION
int		execute(t_node *node);
int		execute_execve(char **cmd_arg, t_var *var_lst);
int		execute_builtins(char **cmd_arg, t_var *var_lst);
int		execute_subshell(t_subshell *subshell);
int		execute_simple_cmd(t_simple_command *sc);

// HANDLE Quotes & Env_Expansion
void	handle_quotes_n_var_expansion(char ***cmd_arg, t_var *var_lst);
void	ft_split_cmd_str_after_expansion(char ***cmd_arg, char *cmd_str,
			int str_index);

// * PIPES
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
int		build_pipes(t_pipe *pipe_node);

#endif