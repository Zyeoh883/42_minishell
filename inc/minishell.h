/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:04:32 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/29 15:49:40 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <signal.h>

# include "../libft/libft.h"
# include "data_structs.h"
# include "execute.h"

# include "../libft/libft.h"
# include "create_node.h"
# include "tokenize.h"
# include "data_structs.h"
# include "history.h"
# include "readline.h"
# include "readline_input.h"

// MACROS
// # define SUCCESS 0
// # define FAIL 1
// # define AND 0
// # define OR 1
# define OFF 0
# define ON 1

// EXIT CODES
# define SIGNALINT 130
# define TOKEN_FAIL 258
# define ERR_CMD_NOT_EXECUTABLE 126
# define ERR_PERMISSION_DENIED 126
# define ERR_CMD_NOT_FOUND 127
# define ERR_NO_SUCH_FILE_OR_DIR 127
# define NOT_BUILTIN -1

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


// readline

// char	*add_to_line(char *input, char *add_on, char hanging_char);

// free
void	free_str_arr(char **str_arr);
void	free_var_lst(t_var *list);

// utils
void	perror_and_exit(char *str, int exit_code);
int		perror_and_return(char *str, int return_value);
int		print_err_and_return(char *str, char *perror_str, int return_value);
void	if_null_perror_n_exit(void *ptr, char *str, int exit_code);
int		print_custom_err_n_return(char *cmd, char *cmd_arg, char *err_msg,
			int return_value);
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
int	print_env_var(t_var *var_lst, char *add_msg_before_var);
void	print_var_lst(t_var *var_lst);
// Exit Status
void	set_exit_status(int exit_code, t_var *var_lst);

#endif
