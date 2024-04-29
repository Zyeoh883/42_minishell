/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/04/29 16:08:55 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"



char *expand_var(char *str, char **my_env)
{
	int i;
	char *result;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			
		}
		
	}
	
	free(str); // TODO: only free if str is changed
	return (result);
}

int handle_quotes_n_var_expansion(char **cmd, char **my_env)
{
	char *tmp;
	int i;
	int expand;
	
	i = -1;
	
	while (cmd[++i])
	{
		expand = ON; // ON by default
		if (cmd[i][0] == '\'') // single quote
			expand = OFF;
		if (cmd[i][0] == '\'' || cmd[i][0] == '\"') 
			tmp = ft_strtrim(cmd[i], cmd[i][0]);
		
		if (expand == ON);
			tmp = expand_var(tmp, my_env); // TODO ,search for $, remalloc, free old str
			
		replace_str(&cmd[i], tmp); // TODO, 
			// remalloc & free
			
	}
}