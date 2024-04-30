/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/30 15:53:18 by sting            ###   ########.fr       */
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

// MACROS
# define SUCCESS 0
# define FAIL 1
# define AND 0
# define OR 1
# define OFF 0
# define ON 1

// EXIT CODES
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_CMD_NOT_EXECUTABLE 126
# define SIGNALINT 130

t_node	*create_node(t_nodetype type);
t_node	*create_simple_command(t_env_var *env_lst, char **cmd);



// * EXECUTION
int		execute_execve(char **cmd_arg, char **env);
int		execute(t_node *node);

// ENV
char	*my_getenv(const char *name, char **my_env);
t_env_var	*convert_env_to_linked_list(char **env);
char	**convert_env_lst_to_array(t_env_var *env_list);

// BUILT-INS
// void	execute_env(char **my_env);

// * PIPES
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
int		build_pipes(t_pipe *pipe_node);

// free
void	free_str_arr(char **str_arr);
void free_env_lst(t_env_var *list);

// utils
void	perror_and_exit(char *str, int exit_code);
void	free_split(char **split);
void	output_token_error(char *str);

#endif
