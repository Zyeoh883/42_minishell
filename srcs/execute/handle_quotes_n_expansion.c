/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/05/06 13:42:45 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void expand_str(char **str_add, char **my_env)
// {
// 	int i; // index of $ sign
// 	int j; // index of non-alnum char right after var_name
// 	int size;
// 	char *str;
// 	char *value;
// 	char *var_name;
// 	char *expanded;

// 	str = *str_add;
// 	if (ft_strchr(*str_add, '$') == NULL)
// 		return ;
// 	i = -1;
// 	while (str[++i]) // find index of $
// 	{
// 		if (str[i] == '$' && str[i + 1] != '\0')
// 		{
// 			j = i + 1;
// 			while (str[j] && ft_isalnum(str[j]))
// 				j++; // find index of non alnum chars after var_name
// 			var_name = ft_substr(str, i + 1, j - i - 1);
// 			value = my_getenv(var_name, my_env);
// 			if (value == NULL)
// 				value = ""; // ! if var not found in my_env, expand to ""
// 			size = i + ft_strlen(value) + ft_strlen(str) - j;
// 			expanded = (char *)malloc(sizeof(char) * (size + 1));
// 			if_null_perror_n_exit(expanded, "malloc", EXIT_FAILURE);
// 			ft_strlcpy(expanded, str, i + 1); // +1 as 3rd param includes
// 			ft_strlcpy(&expanded[i], value, ft_strlen(value) + 1);
// 			ft_strlcpy(&expanded[i + ft_strlen(value)], &str[j], ft_strlen(str)
// 				- j + 1);
// 			expanded[size] = '\0';
// 			free(*str_add);
// 			*str_add = expanded;
// 			return ;
// 		}
// 	}
// }

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

/*
	int		i; -> index of $ sign
	int		j; -> index of char right after var_name
*/
void	expand_str(char **str_add, char **my_env)
{
	int		size;
	char	*str;
	char	*value;
	char	*var_name;
	char	*expanded;
	int		i;
	int		j;

	str = *str_add;
	if (ft_strchr(*str_add, '$') == NULL)
		return ;
	i = -1;
	while (str[++i] && !(str[i] == '$' && str[i + 1] != '\0'))
		; // find index of $
	if (str[i] == '\0')
		return ;
	j = get_index_of_char_after_var_name(str, i);
	var_name = ft_substr(str, i + 1, j - i - 1);
	value = my_getenv(var_name, my_env);
	if (value == NULL)
		value = ""; // ! if var not found in my_env, expand to ""
	size = i + ft_strlen(value) + ft_strlen(str) - j;
	expanded = (char *)malloc(sizeof(char) * (size + 1));
	if_null_perror_n_exit(expanded, "malloc", EXIT_FAILURE);
	ft_strlcpy(expanded, str, i + 1); // +1 as 3rd param includes
	ft_strlcpy(&expanded[i], value, ft_strlen(value) + 1);
	ft_strlcpy(&expanded[i + ft_strlen(value)], &str[j], ft_strlen(str) - j
		+ 1);
	expanded[size] = '\0';
	free(*str_add);
	*str_add = expanded;
}

void	trim_quotes(char **str_add, char *quote_type)
{
	char	*trimmed_str;

	trimmed_str = ft_strtrim(*str_add, quote_type);
	if_null_perror_n_exit(trimmed_str, "ft_strtrim", EXIT_FAILURE);
	free(*str_add);
	*str_add = trimmed_str;
}

void	handle_quotes_n_var_expansion(char **cmd, char **my_env)
{
	int	i;
	int	expand;

	(void)my_env;
	i = -1;
	while (cmd[++i])
	{
		expand = ON;           // ON by default
		if (cmd[i][0] == '\'') // single quote
		{
			expand = OFF;
			trim_quotes(&cmd[i], "\'");
		}
		else if (cmd[i][0] == '\"') // double quote
			trim_quotes(&cmd[i], "\"");
		if (expand == ON)
			expand_str(&cmd[i], my_env);
	}
}
