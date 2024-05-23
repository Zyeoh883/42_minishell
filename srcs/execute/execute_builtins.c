/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:04:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/23 13:40:26 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int j;  j -> index of '='
*/
int	execute_export(char **cmd_arg, t_var *var_lst)
{
	int		i;
	int		j;
	char	*var_name;
	t_var	*node;

	if (cmd_arg[1] == NULL || cmd_arg[1][0] == '#')
	{
		print_env_var(var_lst, "declare -x ");
		return (EXIT_SUCCESS);
	}
	i = 0;
	while (cmd_arg[++i] != NULL)
	{
		// error check for var_name: not a valid idenifier
		j = -1;
		if (!ft_isalpha(cmd_arg[i][0]) && cmd_arg[i][0] != '_')
			return (print_custom_err_n_return("export: `", cmd_arg[i],
					"\': not a valid identifier", EXIT_FAILURE));
		while (cmd_arg[i][++j] && cmd_arg[i][j] != '=')
			if (!(ft_isalnum(cmd_arg[i][j]) || cmd_arg[i][j] == '_'))
				return (print_custom_err_n_return("export: `", cmd_arg[i],
						"\': not a valid identifier", EXIT_FAILURE));
						
		// search for var_name, check if valid
		var_name = ft_substr(cmd_arg[i], 0, j);
		if_null_perror_n_exit(var_name, "ft_substr", EXIT_FAILURE);
		printf("(export) var_name: %s\n", var_name); // !remove
		node = get_var_node(var_name, var_lst);
		free(var_name);
		
		if (node != NULL) // if variable exist
		{
			node->is_exported = true;
			if (cmd_arg[i][j] == '=')
				set_var_value(var_name, &cmd_arg[i][j + 1], var_lst);
		}
		else // if var don't exist
		{
			if (cmd_arg[i][j] == '=')
				var_lstadd_back(&var_lst, var_lstnew(cmd_arg[i], true));
			else if (cmd_arg[i][j] == '\0') // if str has no '='
				var_lstadd_back(&var_lst, var_lstnew(cmd_arg[i], false));
		}
	}
	print_var_lst(var_lst);
	return (EXIT_SUCCESS);
}

int	execute_cd(char **cmd_arg, t_var *var_lst)
{
	char	cwd[PATH_MAX];
	char	*path;

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

void	execute_pwd(void)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
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
		execute_echo(cmd_arg);
	else if (ft_strcasecmp(*cmd_arg, "env") == 0)
		print_env_var(var_lst, "");
	else if (ft_strcasecmp(*cmd_arg, "cd") == 0)
		return (execute_cd(cmd_arg, var_lst));
	else if (ft_strcasecmp(*cmd_arg, "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(*cmd_arg, "export") == 0)
		return (execute_export(cmd_arg, var_lst));
	return (EXIT_SUCCESS); // ! will built-in fail?
}
