/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/18 15:38:04 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "data_structs.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

t_node	*create_node(t_nodetype type);
t_node	*create_command(char **env, char **cmd);

// execute
void	execute(t_node *node);
void	ex_cmd(t_command *command);
void	ex_simple_command(t_simple_command *simple_command);
void	ex_pipe(t_pipe *pipe);

// BUILT-INS
void	execute_env(char **my_env);

// free
void	free_str_arr(char **str_arr);

// piping
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
int		build_pipes(t_pipe *pipe_node);

#endif
