/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/15 19:53:28 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# include "minishell.h"

typedef enum e_nodetype
{
	SIMPLE_COMMAND,
	COMMAND,
	PIPE,
}								t_nodetype;

typedef struct s_node
{
	t_nodetype					type;
	union //  * Do not typedef union, will result in node->union_name->var
	{
		struct s_pipe			*pipe;
		struct s_command		*command;
		struct s_simple_command	*simple_command;
	};
}								t_node;

typedef struct s_command
{
	char						**env;
	char						**cmd;
}								t_command;

typedef struct s_simple_command // TODO refactor this to handle redir in & out
{
	char **files;
	t_node *cmd; // TODO can be only command or subshell, will rename
}								t_simple_command;

typedef struct s_pipe
{
	int							n_nodes;
	pid_t						*pipe;
	t_node						**arr_nodes;
}								t_pipe;

#endif