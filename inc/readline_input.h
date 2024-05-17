/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_input.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:12:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/17 16:20:44 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READLINE_INPUT_H
# define READLINE_INPUT_H

# include "history.h"
# include "readline.h"

typedef struct s_readline_flags
{
	int	d_quoted;
	int	s_quoted;
}		t_readline_flags;

#endif