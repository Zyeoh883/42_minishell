/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/09 19:43:47 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

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
	union
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

// typedef struct s_redir
// {
// 	t_node			*input;
// 	t_node			*output;
// }					t_command;

typedef struct s_pipe
{
	int						n_nodes;
	t_node					*arr_nodes;
	pid_t					*pipe;
	int						fd_in;
	int						fd_out;
}							t_pipe;

#endif