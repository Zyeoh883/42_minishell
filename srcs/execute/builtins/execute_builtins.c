/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/06/04 10:43:57by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_env_var(t_var *var_lst, char *add_msg_before_var)
{
	while (var_lst != NULL)
	{
		if (var_lst->is_exported && ft_strchr(var_lst->str, '=') != NULL)
		{
			if (add_msg_before_var && add_msg_before_var[0] != '\0')
				ft_printf("%s", add_msg_before_var);
			ft_printf("%s\n", var_lst->str);
		}
		var_lst = var_lst->next;
	}
	return (EXIT_SUCCESS);
}

int	execute_pwd(void)
{
	char	cwd[PATH_MAX];

	printf(">>>>>BUILT_IN>>>>>\n");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int	execute_builtins(char **cmd_arg, t_var *var_lst)
{
	if (ft_strcmp(*cmd_arg, "exit") == 0)
		exit(EXIT_SUCCESS); // ! not done
	else if (ft_strcasecmp(*cmd_arg, "echo") == 0)
		return (execute_echo(cmd_arg));
	else if (ft_strcasecmp(*cmd_arg, "env") == 0)
		return (print_env_var(var_lst, ""));
	else if (ft_strcasecmp(*cmd_arg, "cd") == 0)
		return (execute_cd(cmd_arg, var_lst));
	else if (ft_strcasecmp(*cmd_arg, "pwd") == 0)
		return (execute_pwd());
	else if (ft_strcmp(*cmd_arg, "export") == 0)
		return (execute_export(cmd_arg, var_lst));
	else if (ft_strcmp(*cmd_arg, "unset") == 0)
		return (execute_unset(cmd_arg, var_lst));
	else
		return (NOT_BUILTIN);
}
