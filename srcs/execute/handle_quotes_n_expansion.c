/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/04/30 16:56:30 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


/* 
TODO: search for $, if not found, return str
TODO: 
*/
char *expand_var(char *str, char **my_env)
{
	int i;
	char *result;
	char *value;
	char *substr;

	if (ft_strchr(str, '$') == NULL)
		return (str); // no $ found, return str
	i = -1;
	while (str[++i]) // find index of $
	{
		if (str[i] == '$' && str[i + 1] != '\0') 
		{
			// store value
			value = my_getenv(&str[i + 1], my_env);
			if (value == NULL)
				value = ""; // ! if var not found in my_env, expand to ""
			break ;
		}
	}
	substr = ft_substr(str, 0, i);
	result = ft_strjoin(substr, value);
	free(substr);
	free(str);
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
		{
			tmp = ft_strtrim(cmd[i], cmd[i][0]);
			if (tmp == NULL)
				perror_and_exit("ft_strtrim", EXIT_FAILURE);
		}
		if (expand == ON);
			tmp = expand_var(tmp, my_env); // TODO ,search for $, remalloc, free old str
			
		replace_str(&cmd[i], tmp); // TODO, 
			// remalloc & free
			
	}
}
