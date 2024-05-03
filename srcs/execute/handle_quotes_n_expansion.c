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
// char *return_expanded_str(char *str, char **my_env)
// {
// 	int i;
// 	char *result;
// 	char *value;
// 	char *substr;
	
// 	if (str == NULL) // *testing
// 		printf("str is NULL\n");
// 	if (ft_strchr(str, '$') == NULL)
// 		return (str); // no $ found, return str
// 	i = -1;
// 	while (str[++i]) // find index of $
// 	{
// 		if (str[i] == '$' && str[i + 1] != '\0') 
// 		{
// 			// store value
// 			value = my_getenv(&str[i + 1], my_env);
// 			if (value == NULL)
// 				value = ""; // ! if var not found in my_env, expand to ""
// 			substr = ft_substr(str, 0, i);
// 			if_null_perror_n_exit(substr, "ft_substr", EXIT_FAILURE);
// 			result = ft_strjoin(substr, value);
// 			if_null_perror_n_exit(result, "ft_strjoin", EXIT_FAILURE);
// 			free(substr);
// 			return (result);
// 		}
// 	}
// 	return(str);
// 	// free(str); // ! don't free because str is a copy?
// }

void expand_str(char **str_add, char **my_env)
{
	char *str;
	int i;
	char *value;
	char *substr_front;
	// char *substr_back;
	char *result;

	str = *str_add;
	if (ft_strchr(*str_add, '$') == NULL)
		return ;
	i = -1;
	while (str[++i]) // find index of $
	{
		if (str[i] == '$' && str[i + 1] != '\0') 
		{
			// store value
			// TODO: sotre
			value = my_getenv(&str[i + 1], my_env);
			if (value == NULL)
				value = ""; // ! if var not found in my_env, expand to ""

			substr_front = ft_substr(str, 0, i);
			if_null_perror_n_exit(substr_front, "ft_substr", EXIT_FAILURE);
			result = ft_strjoin(substr_front, value);
			if_null_perror_n_exit(result, "ft_strjoin", EXIT_FAILURE);
			free(substr_front);	
			
			// save chars behind var_name
			// while (str[i] && ft_isalnum(str[i++])); // find index of non alnum chars after var_name
			// substr_back = ft_substr(str, i, ft_strlen(str));
			free(*str_add);
			*str_add = result;
			return ;
		}
	}
}

// quote_type: "\'" OR "\""
void trim_quotes(char **str_add, char *quote_type)
{
	char *trimmed_str;

	trimmed_str = ft_strtrim(*str_add, quote_type);
	if_null_perror_n_exit(trimmed_str, "ft_strtrim", EXIT_FAILURE);
	free(*str_add);
	*str_add = trimmed_str;
}

void handle_quotes_n_var_expansion(char **cmd, char **my_env)
{
	// char *trimmed_str = NULL;
	// char *expanded_str = NULL;
	int i;
	int expand;
	
	(void)my_env;
	i = -1;
	
	while (cmd[++i])
	{
		expand = ON; // ON by default
		if (cmd[i][0] == '\'') // single quote
		{
			expand = OFF;
			trim_quotes(&cmd[i], "\'");
		}
		else if (cmd[i][0] == '\"') // double quote
			trim_quotes(&cmd[i], "\"");

		// printf("trimmed: %s\n", cmd[i]);
		if (expand == ON)
			expand_str(&cmd[i], my_env);
		// printf("expanded: %s\n", cmd[i]);

		// 	expanded_str = return_expanded_str(trimmed_str, my_env);
		// free(trimmed_str);	// ! double free: as return_expanded_str could be the original str->"trimmed_str" if there's no $
		// update_ori_cmd_array(&cmd[i], expanded_str); // TODO, remalloc & free
	}
}
