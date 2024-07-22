/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   does_entry_match_wildcard_str.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:30:14 by sting             #+#    #+#             */
/*   Updated: 2024/07/22 10:44:50 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	does_first_token_match(char **entry_str, t_token **w_token)
{
	if ((*w_token)->value[0] != '*' || (*w_token)->type == QUOTED)
	{
		if (ft_strncmp((*w_token)->value, *entry_str,
				ft_strlen((*w_token)->value)) == 0)
		{
			*entry_str += ft_strlen((*w_token)->value);
			(*w_token) = (*w_token)->next;
		}
		else
			return (false);
	}
	return (true);
}

/*
while (not last_token)
{
	if ('*')
		skip;
	if (w_token->str is non-'*' but entry_str has iterated to \0)
		return (false);
	ft_strnstr -> check if w_token->str has a match in entry_str;
	if (no match found)
		return (false)
	else
		update entry_str to point to char right after 
			matched set_of_char in entry_str;
}

*/
bool	does_mid_tokens_match(char **entry_str, t_token **w_token)
{
	while ((*w_token) && (*w_token)->next)
	{
		if ((*w_token)->value[0] == '*' && (*w_token)->type != QUOTED)
		{
			(*w_token) = (*w_token)->next;
			continue ;
		}
		if (*(*entry_str) == '\0')
			return (false);
		*entry_str = ft_strnstr(*entry_str, (*w_token)->value,
				ft_strlen(*entry_str));
		if (*entry_str == NULL)
			return (false);
		*entry_str += ft_strlen((*w_token)->value);
		(*w_token) = (*w_token)->next;
	}
	return (true);
}

bool	does_last_token_match(char *entry_str, t_token *w_token)
{
	if (w_token && (w_token->value[0] != '*' || w_token->type == QUOTED))
		if (rev_strncmp(w_token->value, entry_str,
				ft_strlen(w_token->value)) != 0)
			return (false);
	return (true);
}

bool	does_entry_match_wildcard_str(char *entry_str, t_token *w_token)
{
	if (entry_str[0] == '.' && w_token->value[0] != '.')
		return (false);
	if (does_first_token_match(&entry_str, &w_token) == false)
		return (false);
	if (does_mid_tokens_match(&entry_str, &w_token) == false)
		return (false);
	return (does_last_token_match(entry_str, w_token));
}
