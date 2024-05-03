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

// void expand_str(char **str_add, char **my_env)
// {
// 	char *str;
// 	int i;
// 	char *value;
// 	char *substr_front;
// 	// char *substr_back;
// 	char *result;

// 	str = *str_add;
// 	if (ft_strchr(*str_add, '$') == NULL)
// 		return ;
// 	i = -1;
// 	while (str[++i]) // find index of $
// 	{
// 		if (str[i] == '$' && str[i + 1] != '\0') 
// 		{
// 			// store value
// 			 // TODO: create substr(for var_name) that ends when encounter non-alnum or \0
// 			value = my_getenv(&str[i + 1], my_env);
// 			if (value == NULL)
// 				value = ""; // ! if var not found in my_env, expand to ""

// 			substr_front = ft_substr(str, 0, i);
// 			if_null_perror_n_exit(substr_front, "ft_substr", EXIT_FAILURE);
// 			result = ft_strjoin(substr_front, value);
// 			if_null_perror_n_exit(result, "ft_strjoin", EXIT_FAILURE);
// 			free(substr_front);	
			
// 			// save chars behind var_name
// 			// while (str[i] && ft_isalnum(str[i++])); // find index of non alnum chars after var_name
// 			// substr_back = ft_substr(str, i, ft_strlen(str));
// 			free(*str_add);
// 			*str_add = result;
// 			return ;
// 		}
// 	}
// }

// void expand_str(char **str_add, char **my_env)
// {
// 	int i;
// 	int j;
// 	char *str;
// 	char *value;
// 	char *substr_front;
// 	char *var_name;
// 	char *substr_back;
// 	char *result;

// 	str = *str_add;
// 	if (ft_strchr(*str_add, '$') == NULL)
// 		return ;
// 	i = -1;
// 	while (str[++i]) // find index of $
// 	{
// 		if (str[i] == '$' && str[i + 1] != '\0') 
// 		{
// 			// store value
// 			// TODO: create substr(for var_name) that ends when encounter non-alnum or \0
			
// 			j = i + 1;
// 			while (str[j] && ft_isalnum(str[j]))
// 				j++; // find index of non alnum chars after var_name
// 			var_name = ft_substr(str, i, j - i); 

// 			value = my_getenv(var_name, my_env);
// 			if (value == NULL)
// 				value = ""; // ! if var not found in my_env, expand to ""
// 			substr_front = ft_substr(str, 0, i);
// 			if_null_perror_n_exit(substr_front, "ft_substr", EXIT_FAILURE);
			
// 			// save chars behind var_name
// 			substr_back = ft_substr(str, j, ft_strlen(str) - j);
// 			if_null_perror_n_exit(substr_back, "ft_substr", EXIT_FAILURE);

// 			result = ft_strjoin(substr_front, value);
// 			if_null_perror_n_exit(result, "ft_strjoin", EXIT_FAILURE);
// 			free(substr_front);	

// 			char *result2 = ft_strjoin(result, substr_back);
// 			if_null_perror_n_exit(result, "ft_strjoin", EXIT_FAILURE);

// 			free(*str_add);
// 			*str_add = result2;
// 			return ;
// 		}
// 	}
// }

void expand_str(char **str_add, char **my_env)
{
	int i; // index of $ sign
	int j; // index of non-alnum char right after var_name
	char *str;
	char *value;
	char *var_name;
	char *result;

	str = *str_add;
	if (ft_strchr(*str_add, '$') == NULL)
		return ;
	i = -1;
	while (str[++i]) // find index of $
	{
		if (str[i] == '$' && str[i + 1] != '\0') 
		{
			j = i + 1;
			while (str[j] && ft_isalnum(str[j]))
				j++; // find index of non alnum chars after var_name
			var_name = ft_substr(str, i + 1, j - i); // ! stopped here friday may 3rd
			printf("var_name: %s\n", var_name);
			value = my_getenv(var_name, my_env);
			if (value == NULL)
				value = ""; // ! if var not found in my_env, expand to ""
			int size = i + ft_strlen(value) + ft_strlen(str) - j;
			result = (char *)malloc(sizeof(char) * size + 1);
			if_null_perror_n_exit(result, "malloc", EXIT_FAILURE);
			ft_strlcpy(result, str, i);
			ft_strlcpy(&result[i], value, ft_strlen(value));
			ft_strlcpy(&result[i + ft_strlen(value)], &str[j], ft_strlen(str) - j);
			result[size] = '\0';
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
