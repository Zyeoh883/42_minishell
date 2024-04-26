/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/26 14:02:11 by sting            ###   ########.fr       */
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
	INPUT,
	OUTPUT,
};


typedef struct s_node
{
	t_nodetype					type;
	union //  * Do not typedef union, will result in node->union_name->var
	{
		struct s_pipe			*pipe;
		struct s_subshell		*subshell;
		struct s_and_or			*and_or;
		struct s_simple_command	*simple_command;
	};
}								t_node;

typedef struct s_subshell
{
	t_node						*node;
}								t_subshell;

typedef struct s_and_or
{
	int *operators; // ! update
	t_node						**arr_nodes;
} t_and_or; // ! update

typedef struct s_pipe
{
	int							n_nodes;
	t_node **arr_nodes; // children
	pid_t						*pipe;
	int							fd_in;
	int							fd_out;
}								t_pipe;

typedef struct s_redir
{
	enum e_redirtype			type;
	char						*filename;

}								t_redir;

typedef struct s_env_var
{
	char						*str;
	int							is_exported;
	struct s_env_var			*next;
}								t_env_var;

typedef struct s_simple_command
{
	int							fd_in;
	int							fd_out;
	t_redir *redir; // array of redir structs, all arrays must be NULL terminated
	char						**env;
	int							is_built_in;
	char **cmd;         // NULL terminated 2D array
	t_env_var *env_var; // ! update
}								t_simple_command;

#endif
