/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structs.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/10 16:27:57 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_STRUCTS_H
# define DATA_STRUCTS_H

# include "minishell.h"

typedef enum e_nodetype
{
	COMMAND,
	PIPE,
	REDIRECTION,
}							t_nodetype;

typedef struct s_node
{
	t_nodetype				type;
	union //  * Do not typedef union, will result in node->union_name->var
	{
		struct s_pipe		*pipe;
		struct s_command	*command;
	};
}							t_node;

typedef struct s_command
{
	char					**env;
	char					*str;
}							t_command;

typedef struct s_redir_in
{
	t_node			*input;
	t_node			*output;
}					t_redir_in;

typedef struct s_pipe
{
	int						n_nodes;
	t_node					*arr_nodes;
	pid_t					*pipe;
	int						fd_in;
	int						fd_out;
}							t_pipe;

#endif