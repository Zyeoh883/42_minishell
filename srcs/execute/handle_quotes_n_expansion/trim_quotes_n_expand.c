/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 14:15:13 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trim_quotes_n_expand_cmd_arg(t_simple_command *sc)
{
	int	i;
	int	do_ft_split;

	if (!sc->cmd_arg)
		return (EXIT_SUCCESS);
	do_ft_split = false;
	i = -1;
	while ((sc->cmd_arg)[++i])
	{
		expand_var(&sc->cmd_arg[i], sc->var_lst, &do_ft_split);
		if ((sc->cmd_arg)[i][0] == '\0')
			remove_empty_arg(&sc->cmd_arg, i--);
		else if (do_ft_split == true)
			ft_split_cmd_arg_after_expansion(&sc->cmd_arg, i);
	}
	i = -1;
	while ((sc->cmd_arg)[++i])
		if (trim_quotes_n_expand_asterisk_args(&sc->cmd_arg,
				&i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// "ambiguous redirect" -> if filename is a non-existing variable
int	trim_quotes_n_expand_filename(t_redir ***redir, t_var *var_lst)
{
	int		i;
	int		do_ft_split;
	char	*ori_filename;

	if (!redir || !(*redir))
		return (EXIT_SUCCESS);
	do_ft_split = false;
	i = -1;
	while ((*redir)[++i])
	{
		ori_filename = ft_strdup_w_check((*redir)[i]->filename);
		expand_var(&(*redir)[i]->filename, var_lst, &do_ft_split);
		if (do_ft_split && count_words((*redir)[i]->filename) != 1)
		{
			free_n_replace_str(&(*redir)[i]->filename, ori_filename);
			return (print_custom_err_n_return("", (*redir)[i]->filename,
				": ambiguous redirect", EXIT_FAILURE));
		}
		if (trim_quotes_n_expand_asterisk_redirs(redir, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		free(ori_filename);
	}
	return (EXIT_SUCCESS);
}
