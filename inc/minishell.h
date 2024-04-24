/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/25 02:08:57 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "create_node.h"
# include "data_structs.h"
# include "tokenize.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TOKEN_FAIL 258

t_node	*create_node(t_nodetype type);
t_node	*create_command(char **env, char **cmd);

// execute
void	execute(t_node *node);
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

// utils
void	perror_and_exit(char *str, int exit_code);
void	free_split(char **split);

// error_messages
void	output_token_error(char *str);

#endif
