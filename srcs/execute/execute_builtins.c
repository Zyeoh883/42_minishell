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

void execute_pwd(void)
{
	char cwd[PATH_MAX];
	char *result;

	result = getcwd(cwd, sizeof(cwd));
	if (result == NULL)
	{
		perror("getcwd");
		return ; // ! return?? or RESET minishell loop
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
}

void execute_cd(char **cmd_arg, t_var *var_lst)
{
	char cwd[PATH_MAX];
	char *result;
	char *path;

	path = NULL; // needed?
	result = getcwd(cwd, sizeof(cwd));
	if (result == NULL)
	{
		perror("getcwd");
		return ; // ! return?? or RESET minishell loop
	}
	// TODO: lstaddback OLDPWD if not exist
	if (get_var("OLDPWD", var_lst) == NULL)
		var_lstadd_back(&var_lst, var_lstnew("OLDPWD=", NO));
	if (cmd_arg[1] == NULL)
	{
		path = get_var("HOME", var_lst);
		if (path == NULL)
			
		chdir(path);
	}
	// TODO: update OLDPWD
	set_var("OLDPWD", cwd, var_lst);
	// TODO: update PWD
	set_var("PWD", path, var_lst);
}

void execute_env(char **my_env)
{
	if (!my_env)
		return ; // 
	int i = -1;
	while (my_env[++i] != NULL)
		printf("%s\n", my_env[i]);	
}

// ! need to return int for failure?
void execute_echo(char **cmd_arg)
{
	int i;
	int n_flag;

	n_flag = OFF;
	if (cmd_arg[1] && ft_strlen(cmd_arg[1]) == 2 && ft_strcmp(cmd_arg[1], "-n") == 0)
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
int execute_builtins(char **cmd_arg, t_var *var_lst)
{
	(void)var_lst; // !tmp
	
	// TODO: handle mix of upper & lower case
	if (ft_strcasecmp(*cmd_arg, "echo") == 0)
		execute_echo(cmd_arg);
	else if (ft_strcasecmp(*cmd_arg, "env") == 0)
		print_env_var(var_lst);
	else if (ft_strcasecmp(*cmd_arg, "cd") == 0)
		execute_cd(cmd_arg, var_lst);
	else if (ft_strcasecmp(*cmd_arg, "pwd") == 0)
		execute_pwd();
	return (SUCCESS); // ! will built-in fail?
		
		
}