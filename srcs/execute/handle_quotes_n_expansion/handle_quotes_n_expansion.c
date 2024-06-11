/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/06/11 11:14:37 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quotes(char **str_add)
{
	char	*trimmed_str;

	trimmed_str = ft_substr(*str_add, 1, ft_strlen(*str_add) - 2);
	free(*str_add);
	*str_add = trimmed_str;
}

void	handle_quotes_n_var_expansion(char ***cmd_arg, t_var *var_lst)
{
	int	i;
	int	expand;

	i = -1;
	if (!cmd_arg || !(*cmd_arg))
		return ;
	while ((*cmd_arg)[++i])
	{
		expand = ON;
		if ((*cmd_arg)[i][0] == '\'')
			expand = OFF;
		if ((*cmd_arg)[i][0] == '\'' || (*cmd_arg)[i][0] == '\"')
			trim_quotes(&(*cmd_arg)[i]);
		if (expand == ON && ft_strchr((*cmd_arg)[i], '$') != NULL)
		{
			expand_str(&(*cmd_arg)[i], var_lst);
			if (*((*cmd_arg)[i]) != '\0')
				// if str is empty str (env_var doesn't exist/is empty str)
				ft_split_cmd_str_after_expansion(cmd_arg, (*cmd_arg)[i], i);
		}
	}
}
