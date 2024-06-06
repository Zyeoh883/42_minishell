/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/30 15:55:00 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

typedef enum e_nodetype
{
	// COMMAND,
	// REDIRECTION,
	PIPE,
	SIMPLE_COMMAND,
	SUBSHELL,
	AND_OR,
}								t_nodetype;

enum							e_redirtype
{
	OUTPUT,
	INPUT,
	APPEND,
	HEREDOC,
};

typedef enum e_quote_type
{
	SINGLE,
	DOUBLE,
} 	t_quote_type; 

typedef struct s_var
{
	char						*str;
	int							is_exported;
	struct s_var				*next;
}								t_var;

typedef struct s_node
{
	t_nodetype					type;
	t_var 						*var_lst;
	union //  * Do not typedef union, will result in node->union_name->var
	{
		struct s_pipe			*pipe;
		struct s_subshell		*subshell;
		struct s_and_or			*and_or;
		struct s_simple_command	*simple_command;
	};
}								t_node;

typedef struct s_redir
{
	enum e_redirtype			type;
	char						*filename;
}								t_redir;

typedef struct s_subshell // ! Has redirects
{
	t_redir 					**redir; // array of redir structs, all arrays must be NULL terminated
	t_node						*node;
}								t_subshell;

typedef struct s_and_or
{
	int 						*operators;
	t_node						**arr_nodes; // ? NULL terminated?
} t_and_or;

typedef struct s_pipe
{
	int							n_nodes;
	t_node **arr_nodes; // children
	pid_t						*pipe;
	int							fd_in;
	int							fd_out;
}								t_pipe;

typedef struct s_simple_command
{
	int							fd_in;
	int							fd_out;
	t_redir 					**redir;
	char 						**cmd_arg;  
	t_var 						*var_lst;
}								t_simple_command;

#endif
