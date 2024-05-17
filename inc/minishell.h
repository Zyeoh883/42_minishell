/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/17 16:09:55 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "data_structs.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdbool.h>

// MACROS
# define FAIL 1
# define SUCCESS 0
# define ON 1
# define OFF 0

// EXIT CODES
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_CMD_NOT_EXECUTABLE 126
# define SIGNALINT 130

t_node	*create_node(t_nodetype type, t_var *var_lst);
t_node	*create_simple_command(t_var *env_lst, char **cmd_arg);

// * EXECUTION
// int		execute_execve(char **cmd_arg, char **env);
int		execute(t_node *node);
int		execute_execve(char **cmd_arg, t_var *var_lst);
int		execute_builtins(char **cmd_arg, t_var *var_lst);

// List Functions
// t_var	*var_lstnew(char *str);
t_var	*var_lstnew(char *str, int is_exported);
t_var	*var_lstlast(t_var *lst);
void	var_lstadd_front(t_var **lst, t_var *new);
void	var_lstadd_back(t_var **lst, t_var *new);

// * VARIABLES
// char	*my_getvar(const char *name, char **my_env);
char	*get_var_value(const char *name, t_var *var);
void	set_var_value(char *var_name, char *new_content, t_var *var);
t_var	*get_var_node(const char *name, t_var *var);
t_var	*convert_env_to_linked_list(char **env);
char	**convert_var_lst_to_array(t_var *env_list);
void	print_env_var(t_var *var_lst);
// Exit Status
void	set_exit_status(int exit_code, t_var *var_lst);

// BUILT-INS
// void	execute_env(char **my_env);

// HANDLE Quotes & Env_Expansion
// void handle_quotes_n_var_expansion(char ***cmd_arg, char **my_env);
void	handle_quotes_n_var_expansion(char ***cmd_arg, t_var *var_lst);
void	ft_split_cmd_str_after_expansion(char ***cmd_arg, char *cmd_str,
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
void	print_err_msg(char *err_block, char *msg);
void	print_var_lst(t_var *var_lst);
#endif
