/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sting <sting@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 14:59:30 by sting             #+#    #+#             */
/*   Updated: 2024/06/07 15:37:15 by sting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	execute_cd(char **cmd_arg, t_var *var_lst)
// {
// 	char	cwd[PATH_MAX];
// 	char	*path;

// 	ft_printf(">>>>>BUILT_IN>>>>>\n");

// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 		return (print_err_and_return("getcwd", "", EXIT_FAILURE));
// 	if (get_var_value("OLDPWD", var_lst) == NULL)
// 		var_lstadd_back(&var_lst, var_lstnew("OLDPWD=", true));
// 	set_var_value("OLDPWD", cwd, var_lst);
// 	path = cmd_arg[1];
// 	if (path == NULL || path[0] == '#')
// 	{
// 		path = get_var_value("HOME", var_lst);
// 		if (path == NULL)
// 			return (print_custom_err_n_return("cd: ", "", "HOME not set",
// 					EXIT_FAILURE));
// 	}
// 	if (access(path, F_OK) == -1 || chdir(path) == -1)
// 		return (print_err_and_return("cd: ", path, EXIT_FAILURE));
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 		return (perror_and_return("getcwd", EXIT_FAILURE));
// 	set_var_value("PWD", cwd, var_lst);
// 	return (EXIT_SUCCESS);
// }

int	execute_cd(t_simple_command *sc)
{
	char	cwd[PATH_MAX];
	char	*path;

	ft_printf(">>>>>BUILT_IN>>>>>\n");
	if (setup_redir_without_dup2(sc->redir) == EXIT_FAILURE)
		exit(EXIT_FAILURE);	
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (print_err_and_return("getcwd", "", EXIT_FAILURE));
	if (get_var_value("OLDPWD", sc->var_lst) == NULL)
		var_lstadd_back(&sc->var_lst, var_lstnew("OLDPWD=", true));
	set_var_value("OLDPWD", cwd, sc->var_lst);
	path = sc->cmd_arg[1];
	if (path == NULL || path[0] == '#')
	{
		path = get_var_value("HOME", sc->var_lst);
		if (path == NULL)
			return (print_custom_err_n_return("cd: ", "", "HOME not set",
					EXIT_FAILURE));
	}
	if (access(path, F_OK) == -1 || chdir(path) == -1)
		return (print_err_and_return("cd: ", path, EXIT_FAILURE));
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror_and_return("getcwd", EXIT_FAILURE));
	set_var_value("PWD", cwd, sc->var_lst);
	return (EXIT_SUCCESS);
}
