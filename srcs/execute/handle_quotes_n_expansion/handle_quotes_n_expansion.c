/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes_n_expansion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 15:57:53 by sting             #+#    #+#             */
/*   Updated: 2024/06/25 12:30:33 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_quotes(char **str_add)
{
	char	*trimmed_str;

	trimmed_str = ft_substr(*str_add, 1, ft_strlen(*str_add) - 2);
	free(*str_add);
	*str_add = trimmed_str;
}

void remove_empty_arg(char ***cmd_arg, int index)
{
	int	i;
	int j;
	char **new_arr;
	char **arr;

	arr = *cmd_arg;
	new_arr = (char **)ft_calloc((arr_str_count(arr) - 1) + 1, sizeof(char *));
	if_null_perror_n_exit(new_arr, "ft_calloc", EXIT_FAILURE);
	i = -1;
	j = 0;
	while (arr[++i])
	{
		if (i == index)
			continue ;
		new_arr[j] = ft_strdup(arr[i]);
		if_null_perror_n_exit(new_arr[j], "ft_strdup", EXIT_FAILURE);
		j++;
	}
	free_str_arr(*cmd_arg);
	*cmd_arg = new_arr;
}

char *concatenate_all_str_in_token_lst(t_token *token)
{
	while (token && token->next)
		token_combine_wnext(token);
	return (token->value);
}


void	handle_quotes_n_var_expansion(char ***cmd_arg, t_var *var_lst)
{
	int	i;
	int	expand;
	t_token	*token_root;
	t_token	*token;

	i = -1;
	if (!cmd_arg || !(*cmd_arg))
		return ;
	while ((*cmd_arg)[++i])
	{
		token_root = tokenize_metacharacters((*cmd_arg)[i]);
		format_quotes(token_root);
		token = token_root;
		while (token)
		{
			expand = ON;
			if (token->value[0] == '\'')
				expand = OFF;
			if (token->value[0] == '\'' || token->value[0] == '\"')
				trim_quotes(&token->value);
			if (expand == ON && ft_strchr(token->value, '$') != NULL)
				expand_str(&token->value, var_lst);	
			token = token->next;
		}
		free((*cmd_arg)[i]);
		(*cmd_arg)[i] = concatenate_all_str_in_token_lst(token_root);
		free(token_root);
		if ((*cmd_arg)[i][0] != '\0')
			ft_split_cmd_arg_after_expansion(cmd_arg, (*cmd_arg)[i], i);
		else // if str is empty str (env_var doesn't exist/is empty str)
			remove_empty_arg(cmd_arg, i--);
	}
}
