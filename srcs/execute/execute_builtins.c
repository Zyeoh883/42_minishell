/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/16 13:20:20y sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*result;

	result = getcwd(cwd, sizeof(cwd));
	if (result == NULL)
	{
		perror("getcwd");
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
}

int	execute_cd(char **cmd_arg, t_var *var_lst)
{
	char	cwd[PATH_MAX];
	char	*result;
	char	*path;

	result = getcwd(cwd, sizeof(cwd));
	if (result == NULL)
	{
		perror("getcwd");
		return (EXIT_FAILURE);
	}
	if (get_var_value("OLDPWD", var_lst) == NULL)
		var_lstadd_back(&var_lst, var_lstnew("OLDPWD=", YES));
	set_var_value("OLDPWD", cwd, var_lst);
	path = cmd_arg[1];
	if (path == NULL)
	{
		path = get_var_value("HOME", var_lst);
		if (path == NULL)
		{
			print_err_msg("cd: ", "HOME not set");
			return (EXIT_FAILURE);
		}
	}
	if (access(path, F_OK) == -1 || chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		perror(path);
		return (EXIT_FAILURE);
	}
	set_var_value("PWD", getcwd(cwd, sizeof(cwd)), var_lst);
	return (EXIT_SUCCESS);
}

void	execute_env(char **my_env)
{
	int	i;

	if (!my_env)
		return ; //
	i = -1;
	while (my_env[++i] != NULL)
		printf("%s\n", my_env[i]);
}

// ! need to return int for failure?
void	execute_echo(char **cmd_arg)
{
	int	i;
	int	n_flag;

	n_flag = OFF;
	if (cmd_arg[1] && ft_strlen(cmd_arg[1]) == 2 && ft_strcmp(cmd_arg[1],
			"-n") == 0)
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
}

/*
1. echo
2. cd
3. env
4. export
5. unset
6. pwd
*/
int	execute_builtins(char **cmd_arg, t_var *var_lst)
{
	(void)var_lst; // !tmp

	// TODO: handle mix of upper & lower case
	if (ft_strcasecmp(*cmd_arg, "echo") == 0)
		execute_echo(cmd_arg);
	else if (ft_strcasecmp(*cmd_arg, "env") == 0)
		print_env_var(var_lst);
	else if (ft_strcasecmp(*cmd_arg, "cd") == 0)
		return (execute_cd(cmd_arg, var_lst));
	else if (ft_strcasecmp(*cmd_arg, "pwd") == 0)
		execute_pwd();
	return (SUCCESS); // ! will built-in fail?
}