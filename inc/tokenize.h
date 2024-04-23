/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:57:34 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/23 20:09:00 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZE_H
# define TOKENIZE_H

# include "minishell.h"

typedef enum e_tokentype
{
	QUOTES,
	SUBSHELL,
	AND_OR,
	PIPE,
	SIMPLE_COMMAND,
}						t_tokentype;

typedef struct s_token
{
	char				*value;
	enum e_tokentype	type;
	struct s_token		*next;
}						t_token;

#endif