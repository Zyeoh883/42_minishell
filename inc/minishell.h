/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/21 15:04:41 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# include "../libft/libft.h"
# include "create_node.h"
# include "data_structs.h"
# include "history.h"
# include "readline.h"
# include "tokenize.h"

// MACROS
// # define SUCCESS 0
// # define FAIL 1
// # define AND 0
// # define OR 1
# define OFF 0
# define ON 1
# define YES 1
# define NO 0

// EXIT CODES
# define ERROR_CMD_NOT_FOUND 127
# define ERROR_CMD_NOT_EXECUTABLE 126
# define SIGNALINT 130
# define TOKEN_FAIL 258

# define HERE_DOC_DIR "/tmp/heredoc_"

int		g_signal;

typedef struct s_data // stores all major data
{
	struct sigaction sa;
	t_var *var_lst;
	t_token *token_root;
	t_node *ast_root;
}		t_data;

// Terminal settings
void	reset_terminal(void);

t_node	*create_node(t_nodetype type);
t_node	*create_command(char **env, char **cmd);

// readline
int		minishell_input(t_token **token_root);
char	*handle_readline(char *str);
char	*add_to_line(char *line, char *input);

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
int		perror_and_return(char *str, int return_value);
void	if_null_perror_n_exit(void *ptr, char *str, int exit_code);
void	free_split(char **split);
void	output_token_error(char *str);
int		arr_str_count(char **arr);
void	print_str_arr(char **arr, char *title);
int		ft_strcasecmp(const char *s1, const char *s2);
long	ft_atol(const char *str);

// error_messages
void	output_token_error(char *str);
void	output_eof_error(char quote);

// List Functions
t_var	*var_lstnew(char *str);
t_var	*var_lstlast(t_var *lst);
void	var_lstadd_front(t_var **lst, t_var *new);
void	var_lstadd_back(t_var **lst, t_var *new);

// linked list
t_var	*convert_env_to_linked_list(char **env);
char	**convert_var_lst_to_array(t_var *var_list);
char	*get_var(const char *name, t_var *var);
void	set_var(char *var_name, char *new_content, t_var *var);
void	print_env_var(t_var *var_lst);

#endif
