/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   does_entry_match_wildcard_str.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 16:30:14 by sting             #+#    #+#             */
/*   Updated: 2024/07/18 16:49:25 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool does_first_token_match(char **entry_str, t_token **w_token)
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

bool does_last_token_match(char *entry_str, t_token *w_token)
{
	if (w_token && (w_token->value[0] != '*' || w_token->type == QUOTED))
		if (rev_strncmp(w_token->value, entry_str,
				ft_strlen(w_token->value)) != 0)
			return (false);
	return (true);
}

bool	does_entry_match_wildcard_str(char *entry_str, t_token *w_token)
{
	// bool res;
	
	// todo: default value of res?
	if (entry_str[0] == '.' && w_token->value[0] != '.')
		return (false);
	if (does_first_token_match(&entry_str, &w_token) == false)
		return (false);
	while (w_token && w_token->next)
	{
		if (w_token->value[0] == '*' && w_token->type != QUOTED)
		{
			w_token = w_token->next;
			continue ;
		}
		// if w_token->value is string(not *) but entry_str has iterated to \0
		if (*entry_str == '\0')
			return (false);
		entry_str = ft_strnstr(entry_str, w_token->value, ft_strlen(entry_str));
		if (entry_str == NULL) // str doesn't match
			return (false);
		entry_str += ft_strlen(w_token->value);
		w_token = w_token->next;
	}
	if (w_token && (w_token->value[0] != '*' || w_token->type == QUOTED))
		if (rev_strncmp(w_token->value, entry_str,
				ft_strlen(w_token->value)) != 0)
			return (false);
	return (true);
}
