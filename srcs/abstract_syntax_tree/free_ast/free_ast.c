/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:49:30 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/13 15:11:27 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(t_redir **redir)
{
	int	n;

	if (!redir)
		return ;
	n = -1;
	while (redir[++n])
	{
		if (redir[n]->type == HEREDOC)
			unlink(redir[n]->filename);
		free(redir[n]->filename);
		free(redir[n]);
	}
	free(redir);
}

void	free_and_or(t_and_or *and_or)
{
	int	n;

	n = -1;
	while (and_or->arr_nodes[++n])
		free_ast(and_or->arr_nodes[n]);
	free(and_or->arr_nodes);
	free(and_or->operators);
	free(and_or);
}

void	free_pipe(t_pipe *pipe) // ! Assuming that execution closes & free pipes
{
	int n;

	n = -1;
	while (pipe->arr_nodes[++n])
		free_ast(pipe->arr_nodes[n]);
	free(pipe->arr_nodes);
	free(pipe);
}

void	free_subshell(t_subshell *subshell)
{
	free_redir(subshell->redir);
	free_ast(subshell->node);
	free(subshell);
}

void	free_simple_command(t_simple_command *sc)
{
	free_redir(sc->redir);
	free_str_arr(sc->cmd_arg);
	free(sc);
}

void	free_ast(t_node *node)
{
	if (node->type == SIMPLE_COMMAND)
		free_simple_command(node->simple_command);
	else if (node->type == SUBSHELL)
		free_subshell(node->subshell);
	else if (node->type == PIPE)
		free_pipe(node->pipe);
	else if (node->type == AND_OR)
		free_and_or(node->and_or);
	free(node);
}
