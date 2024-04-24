/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/24 16:43:22 by sting            ###   ########.fr       */
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

enum							e_redirtype
{
	INPUT,
	OUTPUT,
};


// typedef struct s_command
// {
// 	int is_builtin;
// 	char						**env;
// 	char						**cmd;
// }								t_command;

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

typedef struct s_subshell
{
	t_node						*node;
}								t_subshell;	

typedef struct s_andor
{
	char						**operators; // stores "&&"" and "||""
	t_node						**arr_nodes;
}								t_andor; // ! update

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
	int fd_in;
	int fd_out;
	t_redir *redir;  //array of redir structs, all arrays must be NULL terminated
	char **env;
	int is_built_in;
	char  **cmd;    //NULL terminated 2D array
}								t_simple_command;

typedef struct s_redir
{
	enum e_redirtype			type;
	char						*filename;

}								t_redir;

struct							s_env_var
{
	char						*var_name;
	char						*value;
	struct s_env_var			*next;
}								t_env_var;

#endif
