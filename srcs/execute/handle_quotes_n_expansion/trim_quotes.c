/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 11:23:09 by sting             #+#    #+#             */
/*   Updated: 2024/06/24 13:45:45 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

// void	trim_quotes(char **str_add)
// {
// 	char	*trimmed_str;

// 	trimmed_str = ft_substr(*str_add, 1, ft_strlen(*str_add) - 2);
// 	free(*str_add);
// 	*str_add = trimmed_str;
// }

/// @param quote1 index of front quote
/// @param quote2 index of back quote
void remove_quote_pair(char **str_add, int quote1, int quote2)
{
	int	i;
	int	j;
	int	new_size;
	char *new_str;

	new_size = ft_strlen(*str_add) - 2;
	new_str = (char *)ft_calloc(new_size + 1, sizeof(char));
	if_null_perror_n_exit(new_str, "ft_calloc", EXIT_FAILURE);
	// todo: transfer chars execept for quotes
	i = -1;
	j = 0;
	while ((*str_add)[++i])
	{
		if (i == quote1 || i == quote2)
			continue ;
		new_str[j++] = (*str_add)[i];
	}
	free(*str_add);
	*str_add = new_str;
	printf(GREEN"after remove_quote_pair: |%s|"RESET"\n", *str_add);
}

void trim_quotes(char **str_add)
{
	int	i;
	int	j;

	i = -1;
	while ((*str_add)[++i])
	{
		if ((*str_add)[i] == '\'' || (*str_add)[i] == '\"')
		{
			j = i;
			while ((*str_add)[++j])
				if ((*str_add)[j] == (*str_add)[i])
					break ;
			remove_quote_pair(str_add, i, j);
			i = j - 2;
		}
	}
}