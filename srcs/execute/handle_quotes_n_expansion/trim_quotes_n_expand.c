/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes_n_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/07/10 14:54:27 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	trim_quotes_n_expand_cmd_arg(t_simple_command *sc)
// {
// 	int	i;
// 	int do_ft_split;

// 	if (!sc->cmd_arg)
// 		return ;
// 	do_ft_split = false;
// 	i = -1;
// 	while ((sc->cmd_arg)[++i])
// 	{
// 		expand_var(&sc->cmd_arg[i], sc->var_lst, &do_ft_split);
// 		if ((sc->cmd_arg)[i][0] == '\0')
// 			remove_empty_arg(&sc->cmd_arg, i--);
// 		else if (do_ft_split == true)
// 			ft_split_cmd_arg_after_expansion(&sc->cmd_arg, i);
// 	}
// }

// * New Method
void	trim_quotes_n_expand_cmd_arg(t_simple_command *sc)
{
	int	i;
	int do_ft_split;

	if (!sc->cmd_arg)
		return ;
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
	// i = -1;
	// while ((sc->cmd_arg)[++i])
	// {
	// 	// TODO: expand_asterisk()
	// }
	i = -1;
	while ((sc->cmd_arg)[++i])
	{
		// TODO: trim_quotes()
		trim_quotes(&sc->cmd_arg[i]);
	}
}

// * former method
// void	trim_quotes_n_expand_cmd_arg(t_simple_command *sc)
// {
// 	int	i;
// 	int do_ft_split;
// 	t_token	*token;

// 	if (!sc->cmd_arg)
// 		return ;
// 	do_ft_split = false;
// 	i = -1;
// 	while ((sc->cmd_arg)[++i])
// 	{
// 		token = tokenize_metacharacters((sc->cmd_arg)[i]);
// 		format_quotes(token);
// 		print_tokens(token); // ! remove
// 		trim_quotes_n_expand_str(&sc->cmd_arg[i], sc->var_lst, token, &do_ft_split);
// 		// trim_quotes_n_expand_for_all_tokens(token, sc->var_lst, &do_ft_split);
// 		if ((sc->cmd_arg)[i][0] == '\0')
// 			remove_empty_arg(&sc->cmd_arg, i--);
// 		else if (do_ft_split == true)
// 			ft_split_cmd_arg_after_expansion(&sc->cmd_arg, i);
// 		// TODO: expand_asterisk(sc->cmd_arg, token)?
// 			// [] free
// 		// expand_asterisk(&sc->cmd_arg, &token, &i);
// 		// TODO: increment/shift 'i' after '*'expansion
		
// 		// free((sc->cmd_arg)[i]);
// 		// (sc->cmd_arg)[i] = concatenate_all_str_in_token_lst(token);
// 		free_tokens(token);
// 	}
// }

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
		trim_quotes_n_expand_str(&(redir[i]->filename), var_lst, 0);
	}
	return (EXIT_SUCCESS);
}
// "ambiguous redirect" -> if filename is a non-existing variable

// * former method
/*
	remove_empty_arg(cmd_arg, i--);
		^^if str is empty str (as var doesn't exist/is empty str)
*/
// int	trim_quotes_n_expand_filename(t_redir **redir, t_var *var_lst)
// {
// 	int	i;
// 	t_token	*token;

// 	if (!redir || !(*redir))
// 		return (EXIT_SUCCESS);
// 	i = -1;
// 	while (redir[++i])
// 	{
// 		if (redir[i]->filename[0] == '$'
// 			&& get_var_node(&(redir[i]->filename[1]), var_lst) == NULL)
// 			return (print_custom_err_n_return("", redir[i]->filename,
// 					": ambiguous redirect", EXIT_FAILURE));
// 		token = tokenize_metacharacters(redir[i]->filename);
// 		format_quotes(token);
// 		trim_quotes_n_expand_str(&(redir[i]->filename), var_lst, 0);
// 		free_tokens(token);
// 	}
// 	return (EXIT_SUCCESS);
// }
// "ambiguous redirect" -> if filename is a non-existing variable
