/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/08 15:49:25 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
- update/add additional ft_splitted strings to original char **cmd
*/
void ft_split_cmd_str_after_expansion(char ***cmd, char *cmd_str, int str_index)
{
	char **splitted;
	int new_arr_size;
	char **new_arr;
	int i;
	int j;

	splitted = ft_split(cmd_str, ' ');
	if_null_perror_n_exit(splitted, cmd_str, EXIT_FAILURE);
	// calculate new size of cmd_arr
	new_arr_size = arr_str_count(*cmd) - 1 + arr_str_count(splitted);
	// remalloc new arr with added size
	new_arr = (char **)ft_calloc(new_arr_size + 1, sizeof(char *));
	if_null_perror_n_exit(new_arr, "ft_calloc", EXIT_FAILURE);
	// TODO: transfer
	// transfer str(s) until str_index
	i = -1;
	while (++i < str_index)
	{
		new_arr[i] = ft_strdup((*cmd)[i]);
		if_null_perror_n_exit(new_arr[i], "ft_strdup", EXIT_FAILURE);
	}
	// transfer splitted str(s)
	j = 0;
	while (j < arr_str_count(splitted)) // !notsure
	{
		new_arr[i] = (char *)ft_calloc(ft_strlen(splitted[j]) + 1, sizeof(char));
		ft_strlcpy(new_arr[i++], splitted[j], ft_strlen(splitted[j]) + 1);
		j++;
	}
	free_str_arr(splitted);
	// transfer str(s) str_index + 1
	j = str_index + 1;
	while ((*cmd)[j] != NULL)
	{
		new_arr[i] = (char *)ft_calloc(ft_strlen((*cmd)[j]) + 1, sizeof(char));
		if_null_perror_n_exit(new_arr[i], "ft_calloc", EXIT_FAILURE);
		ft_strlcpy(new_arr[i++], (*cmd)[j], ft_strlen((*cmd)[j]) + 1);
		j++;
	}
	// link new_arr to old **cmd  +  FREE
	free_str_arr(*cmd);
	*cmd = new_arr;
}

int	get_index_of_char_after_var_name(char *str, int dollar_index)
{
	int j;

	j = dollar_index + 1;
	if (ft_isalpha(str[j]))
	{
		while (str[j] && ft_isalnum(str[j]))
			j++; // find index of non alnum chars after var_name
		return (j);
	}
	else // if var_name starts number/symbol
		return (j + 1);
}

char *construct_expanded_str(char **str, char *value, int i, int j)
{
	int size;
	char *expanded;

	size = i + ft_strlen(value) + (ft_strlen((*str)) - j);
	expanded = (char *)ft_calloc(size + 1, sizeof(char));
	printf("size: %d\n", size);
	if_null_perror_n_exit(expanded, "ft_calloc", EXIT_FAILURE);
	ft_strlcpy(expanded, (*str), i + 1); // +1 as 3rd param includes
	ft_strlcpy(&expanded[i], value, ft_strlen(value) + 1);
	ft_strlcpy(&expanded[i + ft_strlen(value)], &(*str)[j], ft_strlen(*str) - j
		+ 1);
	printf("expanded: %s\n", expanded);
	if (expanded[0] == '\0')
		printf("expanded == \"\"\n");
	return (expanded);
}

/*
	int		i; -> index of $ sign
	int		j; -> index of char right after var_name
*/
void	expand_str(char **str, char **my_env)
{
	char	*value;
	char	*var_name;
	char	*expanded;
	int		i;
	int		j;

	i = -1;
	while ((*str)[++i] && !((*str)[i] == '$' && (*str)[i + 1] != '\0'))
		; // find index of $
	if ((*str)[i] == '\0')
		return ;
	j = get_index_of_char_after_var_name((*str), i);
	var_name = ft_substr((*str), (i + 1), (j - i - 1));
	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
	value = my_getenv(var_name, my_env);
	if (value == NULL)
		value = "\0"; // ! if var not found in my_env, expand to ""
	free(var_name);
	expanded = construct_expanded_str(str, value, i, j);
	free(*str);
	*str = expanded;
}

void	trim_quotes(char **str_add, char *quote_type)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(*str_add, quote_type);
	if_null_perror_n_exit(trimmed_str, "ft_strtrim", EXIT_FAILURE);
	free(*str_add);
	*str_add = trimmed_str;
}

// void	handle_quotes_n_var_expansion(char **cmd, char **my_env)
// {
// 	int	i;
// 	int	expand;

// 	i = -1;
// 	while (cmd[++i])
// 	{
// 		expand = ON;           // ON by default
// 		if (cmd[i][0] == '\'') // single quote
// 		{
// 			expand = OFF;
// 			trim_quotes(&cmd[i], "\'");
// 		}
// 		else if (cmd[i][0] == '\"') // double quote
// 			trim_quotes(&cmd[i], "\"");
// 		if (expand == ON && ft_strchr(cmd[i], '$') != NULL)
// 		{
// 			expand_str(&cmd[i], my_env);
// 			ft_split_cmd_str_after_expansion(&cmd, cmd[i], i);
// 		}
// 	}
// }

void	handle_quotes_n_var_expansion(char ***cmd, char **my_env)
{
	int	i;
	int	expand;

	i = -1;
	while ((*cmd)[++i])
	{
		expand = ON; // ON by default
		if ((*cmd)[i][0] == '\'') // single quote
		{
			expand = OFF;
			trim_quotes(&(*cmd)[i], "\'");
		}
		else if ((*cmd)[i][0] == '\"') // double quote
			trim_quotes(&(*cmd)[i], "\"");
		if (expand == ON && ft_strchr((*cmd)[i], '$') != NULL)
		{
			expand_str(&(*cmd)[i], my_env);
			if (*((*cmd)[i]) != '\0') // if str is empty str (env_var doesn't exist/is empty str)
				ft_split_cmd_str_after_expansion(cmd, (*cmd)[i], i);
			print_str_arr(*cmd, "after EACH expansion & ft_splitting");
		}
	}
}
