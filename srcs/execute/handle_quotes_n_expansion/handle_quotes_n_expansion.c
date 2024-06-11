/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/06/11 11:10:55 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	get_index_of_char_after_var_name(char *str, int dollar_index)
// {
// 	int	j;

// 	j = dollar_index + 1;
// 	if (ft_isalpha(str[j]) || str[j] == '_')
// 	{
// 		j++;
// 		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
// 			j++; // find index of non alnum chars after var_name
// 		return (j);
// 	}
// 	else // if var_name starts number/symbol
// 		return (j + 1);
// }

// char	*construct_expanded_str(char **str, char *value, int i, int j)
// {
// 	int		size;
// 	char	*expanded;

// 	size = i + ft_strlen(value) + (ft_strlen((*str)) - j);
// 	expanded = (char *)ft_calloc(size + 1, sizeof(char));
// 	if_null_perror_n_exit(expanded, "ft_calloc", EXIT_FAILURE);
// 	ft_strlcpy(expanded, (*str), i + 1); // +1 as 3rd param includes
// 	ft_strlcpy(&expanded[i], value, ft_strlen(value) + 1);
// 	ft_strlcpy(&expanded[i + ft_strlen(value)], &(*str)[j], ft_strlen(*str) - j
// 		+ 1);
// 	return (expanded);
// }

// /*
// 	int		i; -> index of $ sign
// 	int		j; -> index of char right after var_name
// */
// // void	expand_str(char **str, char **my_env)
// void	expand_str(char **str, t_var *var_lst)
// {
// 	char	*value;
// 	char	*var_name;
// 	char	*expanded;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	while ((*str)[++i] && !((*str)[i] == '$' && (*str)[i + 1] != '\0'))
// 		; // find index of $
// 	if ((*str)[i] == '\0')
// 		return ;
// 	j = get_index_of_char_after_var_name((*str), i);
// 	var_name = ft_substr((*str), (i + 1), (j - i - 1));
// 	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
// 	printf(GREEN"var_name: |%s|"RESET"\n", var_name); // ! remove
// 	value = get_var_value(var_name, var_lst);
// 	if (value == NULL)
// 		value = "\0"; // ! if var not found in my_env, expand to ""
// 	free(var_name);
// 	expanded = construct_expanded_str(str, value, i, j);
// 	free(*str);
// 	*str = expanded;
// }

void	trim_quotes(char **str_add, char *quote_type)
{
	char	*trimmed_str;

	(void)quote_type; // ! remove
	// trimmed_str = ft_strtrim(*str_add, quote_type);
	// if_null_perror_n_exit(trimmed_str, "ft_strtrim", EXIT_FAILURE);
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
			trim_quotes(&(*cmd_arg)[i], "\"");
		if (expand == ON && ft_strchr((*cmd_arg)[i], '$') != NULL)
		{
			expand_str(&(*cmd_arg)[i], var_lst);
			if (*((*cmd_arg)[i]) != '\0')
				// if str is empty str (env_var doesn't exist/is empty str)
				ft_split_cmd_str_after_expansion(cmd_arg, (*cmd_arg)[i], i);
		}
	}
}
