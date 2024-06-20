/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:17:35 by sting             #+#    #+#             */
/*   Updated: 2024/06/20 10:34:18 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "minishell.h"

# define OUTPUT_PERMISSIONS (O_WRONLY | O_CREAT | O_TRUNC)
# define APPEND_PERMISSIONS (O_WRONLY | O_CREAT | O_APPEND)
# define IN 0
# define OUT 1

typedef enum e_builtin_type
{
	EXPORT,
	UNSET,
	ASSIGNMENT,
}		t_builtin_type;

// * EXECUTION
int		execute_ast(t_node *node);
int		execute_execve(t_simple_command *sc);
int		execute_subshell(t_subshell *subshell, t_var *var_lst);
int		execute_simple_cmd(t_simple_command *sc);
int		waitpid_n_get_exit_status(pid_t pid);

// HANDLE Quotes & Env_Expansion
void	handle_quotes_n_var_expansion(char ***cmd_arg, t_var *var_lst);
void	expand_str(char **str, t_var *var_lst);
void	ft_split_cmd_str_after_expansion(char ***cmd_arg, char *cmd_str,
			int str_index);

// Redirection
int		setup_redir(t_redir **redir);
int		open_redir_fds(t_redir **redir, int *fd, t_var *var_lst);
void	dup2_fdin_n_fdout(int *fd);
void	close_fdin_n_fdout(int *fd);

// Builtins
int		execute_builtins(t_simple_command *sc);
int		execute_export(t_simple_command *sc);
int		execute_cd(t_simple_command *sc);
int		execute_unset(t_simple_command *sc);
int		execute_echo(t_simple_command *sc);
// void	update_or_add_variable(t_var *var_lst, char **cmd_arg, int index,
// 			int equal_index);
void	update_or_add_variable(t_simple_command *sc, int index,
		int equal_index, t_builtin_type type);
int		execute_assignment(t_simple_command *sc);
int		is_assignment(char *cmd_arg);
void	remove_assignments_if_cmd_present(char ***cmd_arg);

// Builtin utils
int		count_chars_until_equal_sign(char *str);
int		is_var_name_valid(char *var_name);
int		print_env_var(t_var *var_lst, char *add_msg_before_var);

// * PIPES
int		execute_pipe(t_pipe *pipe);
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
void	build_pipes(t_pipe *pipe_node);

#endif