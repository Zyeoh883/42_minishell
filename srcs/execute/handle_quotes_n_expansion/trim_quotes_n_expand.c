/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/06/25 15:53:15 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quotes_n_expand_cmd_arg(t_simple_command *sc)
{
	int	i;

	i = -1;
	if (!sc->cmd_arg)
		return ;
	while ((sc->cmd_arg)[++i])
	{
		// trim_quotes_n_expand_str(&((*cmd_arg)[i]), var_lst);
		trim_quotes_n_expand_str(&sc->cmd_arg, i, sc->var_lst);
		if ((sc->cmd_arg)[i][0] != '\0')
			ft_split_cmd_arg_after_expansion(&sc->cmd_arg, (sc->cmd_arg)[i], i);
		else
			remove_empty_arg(&sc->cmd_arg, i--);
	}
}
/*
	remove_empty_arg(cmd_arg, i--);
		^^if str is empty str (as var doesn't exist/is empty str)
*/

int	trim_quotes_n_expand_filename(t_redir **redir, t_var *var_lst)
{
	int	i;

	if (!redir || !(*redir))
		return (EXIT_SUCCESS);
	i = -1;
	while (redir[++i])
	{
		if (redir[i]->filename[0] == '$'
			&& get_var_node(&(redir[i]->filename[1]), var_lst) == NULL)
			return (print_custom_err_n_return("", redir[i]->filename,
					": ambiguous redirect", EXIT_FAILURE));
		trim_quotes_n_expand_str(&(redir[i]->filename), var_lst);
	}
	return (EXIT_SUCCESS);
}
// "ambiguous redirect" -> if filename is a non-existing variable