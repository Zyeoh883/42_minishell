/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/25 16:58:09 by sting            ###   ########.fr       */
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
# define SUCCESS 0
# define FAIL 1
# define AND 0
# define OR 1

// EXIT CODES
# define ERROR_CMD_NOT_FOUND 127
# define SIGNALINT 130

t_node	*create_node(t_nodetype type);
// t_node	*create_command(char **env, char **cmd);
t_node	*create_simple_command(char **env, char **cmd);


// execute
int	execute(t_node *node);
// void	ex_cmd(t_command *command);
// void	ex_simple_command(t_simple_command *simple_command);
// void	ex_pipe(t_pipe *pipe);
int execute_execve(char **cmd_arg, char **env);

// BUILT-INS
// void	execute_env(char **my_env);

// free
void	free_str_arr(char **str_arr);

// piping
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
int		build_pipes(t_pipe *pipe_node);

#endif
