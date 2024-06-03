/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_input.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:12:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/06/03 18:44:40 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_INPUT_H
# define READLINE_INPUT_H

# include "minishell.h"

typedef struct s_readline_flags
{
	int	d_quoted;
	int	s_quoted;
}		t_readline_flags;

int		minishell_input(t_token **token_root);
char	*add_to_line(char *input, char *add_on);
char	*pad_input_addon(t_token *token_root, char *input_addon);
char	*handle_addon(char *input, t_token *token_root);

#endif