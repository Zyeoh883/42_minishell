/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:20:09 by sting             #+#    #+#             */
/*   Updated: 2024/06/25 16:26:47 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// iterates through str until char doesn't meet requirements of a valid var_name
int	get_index_of_char_after_var_name(char *str, int dollar_index)
{
	int	j;

	j = dollar_index + 1;
	if (ft_isalpha(str[j]) || str[j] == '_')
	{
		j++;
		while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
			j++;
		return (j);
	}
	else
		return (j + 1);
}

/*
- returns expanded ver of str

	int		d; -> index of $ sign
	int		c; -> index of char right after var_name
*/
char	*construct_expanded_str(char *str, char *value, int d, int c)
{
	int		size;
	char	*expanded;

	size = d + ft_strlen(value) + (ft_strlen((str)) - c);
	expanded = (char *)ft_calloc(size + 1, sizeof(char));
	if_null_perror_n_exit(expanded, "ft_calloc", EXIT_FAILURE);
	ft_strlcpy(expanded, (str), d + 1);
	ft_strlcpy(&expanded[d], value, ft_strlen(value) + 1);
	ft_strlcpy(&expanded[d + ft_strlen(value)], &(str)[c], ft_strlen(str) - c
		+ 1);
	return (expanded);
}

/*
	Return Value: index of char right after expanded value

	process:
		1) Extract var_name from str
		2) Get var value
		3) Replace value with var_name in str
*/
int	expand_single_var(char **str_add, int dollar_index, t_var *var_lst)
{
	int		c;
	char	*var_name;
	char	*value;
	char	*expanded;

	c = get_index_of_char_after_var_name(*str_add, dollar_index);
	var_name = ft_substr(*str_add, (dollar_index + 1), (c - dollar_index - 1));
	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
	value = get_var_value(var_name, var_lst);
	if (value == NULL)
		value = "\0";
	free(var_name);
	expanded = construct_expanded_str(*str_add, value, dollar_index, c);
	free(*str_add);
	*str_add = expanded;
	return (dollar_index + ft_strlen(value));
}

// str_add -> address of str
void	expand_str(char **str_add, t_var *var_lst)
{
	int	i;

	i = 0;
	while ((*str_add)[i])
	{
		if ((*str_add)[i] == '$' && (*str_add)[i + 1] != '\0')
			i = expand_single_var(str_add, i, var_lst);
		else
			i++;
	}
}
