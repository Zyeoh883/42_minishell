/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/02 15:49:16ting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
	- replaces original location of str with trimmed/expanded str
	- free old str
*/
void update_ori_cmd_array(char **str, char *updated_str)
{
	free(*str);
	str = &updated_str;
}

/* 
TODO: NOTDON -> Takes in address of str, replaces the location with a new str, 
free the old one
*/
char *return_expanded_str(char *str, char **my_env)
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
			substr = ft_substr(str, 0, i);
			if (substr == NULL)
				perror_and_exit("ft_substr", EXIT_FAILURE);
			result = ft_strjoin(substr, value);
			if (result == NULL)
				perror_and_exit("ft_strjoin", EXIT_FAILURE);
			free(substr);
			return (result);
		}
	}
	return(str);
	// free(str); // ! don't free because str is a copy?
}


void handle_quotes_n_var_expansion(char **cmd, char **my_env)
{
	char *trimmed_str;
	char *expanded_str = NULL;
	int i;
	int expand;
	
	i = -1;
	
	while (cmd[++i])
	{
		expand = ON; // ON by default
		if (cmd[i][0] == '\'') // single quote
		{
			expand = OFF;
			trimmed_str = ft_strtrim(cmd[i], "\"");
			if (trimmed_str == NULL)
				perror_and_exit("ft_strtrim", EXIT_FAILURE);
		}
		else if (cmd[i][0] == '\"') // double quote
		{
			trimmed_str = ft_strtrim(cmd[i], "\"");
			if (trimmed_str == NULL)
				perror_and_exit("ft_strtrim", EXIT_FAILURE);
		}
		if (expand == ON)
			expanded_str = return_expanded_str(trimmed_str, my_env);
		free(trimmed_str);	// ! double free: as return_expanded_str could be the original str->"trimmed_str" if there's no $
		update_ori_cmd_array(&cmd[i], expanded_str); // TODO, remalloc & free
	}
}
