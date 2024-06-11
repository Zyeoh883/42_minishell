/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 11:08:27 by sting             #+#    #+#             */
/*   Updated: 2024/06/11 14:25:13 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	get_index_of_char_after_var_name(char *str, int dollar_index)
{
	int	j;

	j = dollar_index + 1;
	if (ft_isalpha(str[j]) || str[j] == '_')
	{
		j++;
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++; // find index of non alnum chars after var_name
		return (j);
	}
	else // if var_name starts number/symbol
		return (j + 1);
}
/*
- returns expanded ver of str

	int		i; -> index of $ sign
	int		j; -> index of char right after var_name
*/
char	*construct_expanded_str(char **str, char *value, int i, int j)
{
	int		size;
	char	*expanded;
	
	size = i + ft_strlen(value) + (ft_strlen((*str)) - j);
	expanded = (char *)ft_calloc(size + 1, sizeof(char));
	if_null_perror_n_exit(expanded, "ft_calloc", EXIT_FAILURE);
	ft_strlcpy(expanded, (*str), i + 1); // +1 as 3rd param includes
	ft_strlcpy(&expanded[i], value, ft_strlen(value) + 1);
	ft_strlcpy(&expanded[i + ft_strlen(value)], &(*str)[j], ft_strlen(*str) - j
		+ 1);
	return (expanded);
}

/*
	int		i; -> index of $ sign
	int		j; -> index of char right after var_name
*/
// void	expand_str(char **str, char **my_env)
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

/*
	int		i; -> index of $ sign
	int		j; -> index of char right after var_name
*/
void	expand_str(char **str, t_var *var_lst)
{
	char	*value;
	char	*var_name;
	char	*expanded;
	int		i;
	int		j;

	i = 0;
	while ((*str)[i])
	{
		// printf("Str is [%s]", str[i]);
		if ((*str)[i] == '$' && (*str)[i + 1] != '\0')
		{
			j = get_index_of_char_after_var_name(*str, i);
			printf(GREEN"str[i+1]: |%s|"RESET"\n", &((*str)[i+1])); // ! remove
			printf("len: %i\n", j - i - 1);
			var_name = ft_substr(*str, (i + 1), (j - i - 1));
			if (var_name[0] == '\0')
				printf("var_name[0] == null\n");
			if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
			printf(GREEN"var_name: |%s|"RESET"\n", var_name); // ! remove
			value = get_var_value(var_name, var_lst);
			printf(GREEN"value: %s"RESET"\n", value); // ! remove
			if (value == NULL)
				value = "\0";
			free(var_name);
			expanded = construct_expanded_str(str, value, i, j);
			free(*str);
			*str = expanded;
			printf(GREEN"expanded: %s"RESET"\n", *str); // ! remove
			i += ft_strlen(value);
			printf(GREEN"str[i]: |%s|"RESET"\n", &((*str)[i])); // ! remove
			printf("------\n"); // ! remove
		}
		else 
			i++;
	}
}
