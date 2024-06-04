/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/06/04 09:14:26 by sting            ###   ########.fr       */
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

int	execute_cd(char **cmd_arg, t_var *var_lst)
{
	char	cwd[PATH_MAX];
	char	*path;

	printf(">>>>>BUILT_IN>>>>>\n");
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err_and_return("getcwd", "", EXIT_FAILURE));
	if (get_var_value("OLDPWD", var_lst) == NULL)
		var_lstadd_back(&var_lst, var_lstnew("OLDPWD=", true));
	set_var_value("OLDPWD", cwd, var_lst);
	path = cmd_arg[1];
	if (path == NULL || path[0] == '#')
	{
		path = get_var_value("HOME", var_lst);
		if (path == NULL)
			return (print_custom_err_n_return("cd: ", "", "HOME not set",
					EXIT_FAILURE));
	}
	if (access(path, F_OK) == -1 || chdir(path) == -1)
		return (print_err_and_return("cd: ", path, EXIT_FAILURE));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror_and_return("getcwd", EXIT_FAILURE));
	set_var_value("PWD", cwd, var_lst);
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

// ! need to return int for failure?
int	execute_echo(char **cmd_arg)
{
	int	i;
	int	n_flag;

	printf(">>>>>BUILT_IN>>>>>\n");
	n_flag = OFF;
	if (cmd_arg[1] && ft_strcmp(cmd_arg[1], "-n") == 0)
		n_flag = ON;
	i = 1;
	if (n_flag == ON)
		i = 2;
	while (cmd_arg[i] != NULL)
	{
		ft_putstr_fd(cmd_arg[i], STDOUT_FILENO);
		if (cmd_arg[i + 1] != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (n_flag == OFF)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

// void	execute_echo(char **cmd_arg)
// {
// 	int	i;
// 	int	n_flag;

// 	n_flag = OFF;
// 	i = 1;
// 	while (cmd_arg[i] != NULL)
// 	{
// 		if ((i == 1 || (i > 1 && cmd_arg[i - 1][0] == '\0'))
// 			&& ft_strcmp(cmd_arg[i], "-n") == 0)
// 		{
// 			n_flag = ON;
// 			i++;
// 			continue ;
// 		}
// 		ft_putstr_fd(cmd_arg[i], STDOUT_FILENO);
// 		if (cmd_arg[i + 1] != NULL &&
// ! INSERT code in notion under "solution 2")
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 		i++;
// 	}
// 	if (n_flag == OFF)
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// }

/*
1. echo (done)
2. cd(done)
3. env(done)
4. export
5. unset
6. pwd(done)
*/
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
	else
		return (NOT_BUILTIN);
}
