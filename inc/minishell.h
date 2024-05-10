/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/10 15:10:09 by sting            ###   ########.fr       */
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
# define YES 1
# define NO 0

// EXIT CODES
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_CMD_NOT_EXECUTABLE 126
# define SIGNALINT 130

t_node	*create_node(t_nodetype type);
t_node	*create_simple_command(t_var *env_lst, char **cmd);

// * EXECUTION
// int		execute_execve(char **cmd_arg, char **env);
int	execute_execve(char **cmd_arg, t_var *var_lst);
int		execute(t_node *node);

// List Functions
t_var	*var_lstnew(char *str);

// ENV
// char	*my_getvar(const char *name, char **my_env);
char	*my_getvar(const char *name, t_var *var);
t_var	*convert_env_to_linked_list(char **env);
char	**convert_var_lst_to_array(t_var *env_list);
void	print_env_var(t_var *env_list);

// BUILT-INS
// void	execute_env(char **my_env);

// HANDLE Quotes & Env_Expansion
// void handle_quotes_n_var_expansion(char ***cmd, char **my_env);
void	handle_quotes_n_var_expansion(char ***cmd, t_var *var_lst);
void	ft_split_cmd_str_after_expansion(char ***cmd, char *cmd_str,
			int str_index);

// * PIPES
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
int		build_pipes(t_pipe *pipe_node);

// free
void	free_str_arr(char **str_arr);
void	free_var_lst(t_var *list);

// utils
void	perror_and_exit(char *str, int exit_code);
void	if_null_perror_n_exit(void *ptr, char *str, int exit_code);
void	free_split(char **split);
void	output_token_error(char *str);
int		arr_str_count(char **arr);
void	print_str_arr(char **arr, char *title);

#endif
