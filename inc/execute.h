/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:17:35 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 11:16:25 by sting            ###   ########.fr       */
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
// void	trim_quotes_n_expand_cmd_arg(t_simple_command *sc);
int	trim_quotes_n_expand_cmd_arg(t_simple_command *sc);
int	trim_quotes_n_expand_filename(t_redir ***redir, t_var *var_lst);
void	trim_quotes_n_expand_str(char **str_add, t_var *var_lst,
			int *do_ft_split);
void	trim_quotes_n_expand_for_all_tokens(t_token *token, t_var *var_lst,
			int *do_ft_split);
char	*join_all_str_in_token_lst(t_token *token);
// utils
bool	is_str_quoted(char *str);
void	trim_quotes(char **str_add);
// ? New Method
void	expand_var(char **str_add, t_var *var_lst, int *do_ft_split);
void	trim_quotes_for_all_tokens(t_token *token);

void	trim_quotes(char **str_add);
void	expand_str(char **str, t_var *var_lst);
void	ft_split_cmd_arg_after_expansion(char ***cmd_arg, int str_index);
void	remove_empty_arg(char ***cmd_arg, int index);

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
void	update_or_add_variable(t_simple_command *sc, int index, int equal_index,
			t_builtin_type type);
int		execute_assignment(t_simple_command *sc);
bool	is_assignment(char *cmd_arg);
void	remove_assignments_if_cmd_present(char ***cmd_arg);
int		execute_and_or(t_and_or *and_or);

// Builtin utils
int		count_chars_until_equal_sign(char *str);
bool	is_var_name_valid(char *var_name);
int		print_env_var(t_var *var_lst, char *add_msg_before_var);

// * PIPES
int		execute_pipe(t_pipe *pipe);
void	coupling(t_pipe *pipe_node, int n);
void	close_pipes(t_pipe *pipe_node);
void	build_pipes(t_pipe *pipe_node);

// * WILDCARDS
int		expand_single_asterisk(char ***cmd_arg);
// int	trim_quotes_n_expand_asterisk_args(char ***cmd_arg, int index);
int	trim_quotes_n_expand_asterisk_args(char ***cmd_arg, int *index);

int		trim_quotes_n_expand_asterisk_redirs(t_redir ***redir, int index);

// utils
int		get_directory_entries(t_list **entry_lst);
void	combine_non_asterisk_tokens(t_token *token);
t_token	*replace_token_with_separated_lst(t_token **token_root, t_token *cur,
			t_token *separated_lst);
void	tokenize_asterisks(t_token **token_root);
bool	does_valid_asterisk_exist(t_token *token);
t_list	*gather_matching_entries(t_list *entry, t_token *token);
int		rev_strncmp(const char *s1, const char *s2, size_t n);
bool	does_entry_match_wildcard_str(char *entry_str, t_token *w_token);
void	replace_arg_w_expanded_lst(char ***cmd_arg, int index,
			t_list *expanded_lst);
void	replace_redir_arg_w_expanded_lst(t_redir ***redir, int index,
			t_list *expanded_lst);

#endif
