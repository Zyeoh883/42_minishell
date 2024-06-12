/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:20:09 by sting             #+#    #+#             */
/*   Updated: 2024/06/12 12:23:40 by sting            ###   ########.fr       */
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
char	*construct_expanded_str(char **str, char *value, int d, int c)
{
	int		size;
	char	*expanded;

	size = d + ft_strlen(value) + (ft_strlen((*str)) - c);
	expanded = (char *)ft_calloc(size + 1, sizeof(char));
	if_null_perror_n_exit(expanded, "ft_calloc", EXIT_FAILURE);
	ft_strlcpy(expanded, (*str), d + 1);
	ft_strlcpy(&expanded[d], value, ft_strlen(value) + 1);
	ft_strlcpy(&expanded[d + ft_strlen(value)], &(*str)[c], ft_strlen(*str) - c
		+ 1);
	return (expanded);
}

// returns index of char right after expanded value
int	expand_single_var(char **str, int dollar_index, t_var *var_lst)
{
	int		j;
	char	*var_name;
	char	*value;
	char	*expanded;

	j = get_index_of_char_after_var_name(*str, dollar_index);
	var_name = ft_substr(*str, (dollar_index + 1), (j - dollar_index - 1));
	if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
	value = get_var_value(var_name, var_lst);
	if (value == NULL)
		value = "\0";
	free(var_name);
	expanded = construct_expanded_str(str, value, dollar_index, j);
	free(*str);
	*str = expanded;
	return (dollar_index + ft_strlen(value));
}

// str -> address of str
void	expand_str(char **str, t_var *var_lst)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '$' && (*str)[i + 1] != '\0')
			i = expand_single_var(str, i, var_lst);
		else
			i++;
	}
}
