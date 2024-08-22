/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:19:19 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 13:25:43 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// void	print_spaces_then_str(int len, char *str)
// {
// 	while (len--)
// 		printf(" ");
// 	if (str)
// 		printf("%s", str);
// }

// void	print_ast(t_node *node, int depth)
// {
// 	int		n;
// 	int		i;
// 	char	*sym_redir[4] = {">", "<", ">>", "<<"};
// 	char	*str;

// 	n = -1;
// 	i = -1;
// 	if (node == NULL)
// 		return ;
// 	else if (node->type == SIMPLE_COMMAND)
// 	{
// 		printf("%*s ", depth, "SIMPLE_COMMAND");
// 		while (node->simple_command->redir && node->simple_command->redir[++n])
// 		{
// 			printf("%s ", sym_redir[(node->simple_command->redir[n])->type]);
// 			printf("%s ", (node->simple_command->redir[n])->filename);
// 		}
// 		printf("\n");
// 	}
// 	else if (node->type == SUBSHELL)
// 	{
// 		printf("%s ", "SUBSHELL");
// 		while (node->subshell->redir && node->subshell->redir[++n])
// 		{
// 			printf("%s ", sym_redir[(node->subshell->redir[n])->type]);
// 			printf("%s ", (node->subshell->redir[n])->filename);
// 		}
// 		printf("\n");
// 		print_spaces_then_str(depth * 4, "└─");
// 		print_ast(node->subshell->node, depth + 1);
// 	}
// 	else if (node->type == PIPE)
// 	{
// 		printf("%s\n", "PIPE");
// 		while (node->pipe->arr_nodes[++n])
// 		{
// 			print_spaces_then_str(depth * 4, "└─");
// 			print_ast(node->pipe->arr_nodes[n], depth + 1);
// 		}
// 	}
// 	else if (node->type == AND_OR)
// 	{
// 		printf("%s\n", "AND_OR");
// 		print_spaces_then_str(depth * 4, "└─");
// 		print_ast(node->pipe->arr_nodes[++n], depth + 1);
// 		while (node->pipe->arr_nodes[++n])
// 		{
// 			str = "&&";
// 			if (node->and_or->operators[++i] == OR)
// 				str = "||";
// 			printf("%*s\n", (depth + 1) * 4, str);
// 			print_spaces_then_str(depth * 4, "└─");
// 			print_ast(node->pipe->arr_nodes[n], depth + 1);
// 		}
// 	}
// }
