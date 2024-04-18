/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/18 14:52:54 by sting            ###   ########.fr       */
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
	SIMPLE_CMD,

}							t_nodetype;

typedef struct s_command
{
	char					**env;
	char					**str; // 

}							t_command;

enum e_redirtype
{
	INPUT,
	OUTPUT,
};

typedef struct s_node
{
	t_nodetype				type;
	union //  * Do not typedef union, will result in node->union_name->var
	{
		struct s_pipe		*pipe;
		struct s_command	*command;
		struct s_redir	*redir;
		struct s_simple_cmd *simple_cmd;
	};
}							t_node;

typedef struct s_redir
{
	// t_node			*input;
	// t_node			*output;
	enum e_redirtype type;
	char	*filename;

}					t_redir;

typedef struct s_simple_cmd
{
	t_redir	*redir;
	t_node	*cmd; // ? if there are cmd args, use linked list or array?
	// ^use linked list method for now
}	t_simple_cmd;

typedef struct s_pipe
{
	int						n_nodes;
	t_node					*arr_nodes; // children
	pid_t					*pipe;
	int						fd_in;
	int						fd_out;
}							t_pipe;



#endif
