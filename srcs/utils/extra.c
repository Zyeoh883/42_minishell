/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:02:06 by sting             #+#    #+#             */
/*   Updated: 2024/08/22 10:48:46 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_var_lst(t_var *var_lst)
// {
// 	while (var_lst != NULL)
// 	{
// 		ft_printf("%s\n", var_lst->str);
// 		var_lst = var_lst->next;
// 	}
// }

// void	print_str_arr(char **arr, char *title)
// {
// 	int	i;

// 	printf("\n---%s---\n", title);
// 	i = 0;
// 	while (arr[i])
// 		printf("%s\n", arr[i++]);
// 	printf("-------\n");
// }

// void	print_redir_arr(t_redir **arr)
// {
// 	int	i;

// 	i = -1;
// 	if (!arr)
// 	{
// 		printf("redir_arr is NULL\n");
// 		return ;
// 	}
// 	printf(GREEN"=====Redir arr====="RESET"\n");
// 	while (arr[++i])
// 		printf("%s\n", arr[i]->filename);
// }

// example output> minishell: cd: /invalid_path: "perror message"
int	print_err_and_return(char *str, char *perror_str, int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(str, STDERR_FILENO);
	perror(perror_str);
	return (return_value);
}

/*
eg. print_custom_err_n_return("cd:", ": command not found", EXIT_FAILURE);
*/
int	print_custom_err_n_return(char *cmd, char *cmd_arg, char *err_msg,
		int return_value)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(cmd_arg, STDERR_FILENO);
	ft_putendl_fd(err_msg, STDERR_FILENO);
	return (return_value);
}
