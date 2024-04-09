/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:29:22 by zyeoh             #+#    #+#             */
/*   Updated: 2024/04/09 13:40:18 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H

typedef struct s_node
{
	int		id;
	char	*value;
	t_ast	child;
	t_node	*parent;
}			t_node;

typedef union u_ast
{
	t_node	*left;
	t_node	*right;
	t_node	*arr_node;
}			t_ast;

#endif