/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/21 18:18:56 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

/*
* Structs to add
1. simplecmd
2. builtin_cmd

*/

typedef enum e_nodetype
{
	COMMAND,
	PIPE,
	REDIRECTION,
	SIMPLE_COMMAND,
}								t_nodetype;

typedef struct s_command
{
	int							is_builtin;
	char						**env;
	char						**cmd;
}								t_command;

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
		struct s_command		*command;
		struct s_redir			*redir;
		struct s_simple_command	*simple_command;
	};
}								t_node;

typedef struct s_redir
{
	// t_node			*input;
	// t_node			*output;
	enum e_redirtype			type;
	char						*filename;

}								t_redir;

typedef struct s_simple_command
{
	t_redir						*redir;
	t_node	*cmd; // ? if there are cmd args, use linked list or array?
					// ^use linked list method for now
}								t_simple_command;

typedef struct s_pipe
{
	int							n_nodes;
	t_node **arr_nodes; // children
	pid_t						*pipe;
	int							fd_in;
	int							fd_out;
}								t_pipe;

#endif
