/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:19:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/05/28 17:42:21 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void print_spaces_then_str(int len, char *str)
{
    while (len--)
        printf(" ");
    if (str)
        printf("%s", str);
}

void print_ast(t_node *node, int depth)
{
    char *str;
    
    if (node == NULL)
        return;
    else if (node->type == SIMPLE_COMMAND)
        printf("%*s\n", depth, "SIMPLE_COMMAND");
    else if (node->type == SUBSHELL)
    {
        printf("%s\n", "SUBSHELL");
         print_spaces_then_str(depth * 4, "└─");
        print_ast(node->subshell->node, depth + 1);
    }
    else if (node->type == PIPE)
    {
        printf("%s\n", "PIPE");
        while (*node->pipe->arr_nodes)
        {
             print_spaces_then_str(depth * 4, "└─");
            print_ast(*node->pipe->arr_nodes, depth + 1);
            node->pipe->arr_nodes++;
        }
    }
    else if (node->type == AND_OR)
    {
        printf("%s\n", "AND_OR");
        print_spaces_then_str(depth * 4, "└─");
        print_ast(*node->pipe->arr_nodes, depth + 1);
        node->pipe->arr_nodes++;
        while (*node->pipe->arr_nodes)
        {
            str = "&&";
            if (*node->and_or->operators == OR)
                str = "||";
            printf("%*s\n", (depth + 1) * 4, str);
             print_spaces_then_str(depth * 4, "└─");
            print_ast(*node->pipe->arr_nodes, depth + 1);
            node->pipe->arr_nodes++;
            node->and_or->operators++;
        }
    }
}
