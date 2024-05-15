/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/15 18:06:00 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
		return ;
	// printf("\nminishell reset\n");
	// exit(0);
}

t_var	*init_env(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	if (access("/tmp", F_OK) == -1)
		perror_and_return("access /tmp", 0);
	g_signal = 0;
	return (convert_env_to_linked_list(env));
}

int	main(int argc, char **argv, char **env)
{
	t_data	shell_data;

	ft_memset(&shell_data, 0, sizeof(t_data));
	shell_data.var_lst = init_env(argc, argv, env);
	if (!shell_data.var_lst)
		perror_and_return("Failed to initialize minishell", 0);
	print_env_var(shell_data.var_lst);
	while (1)
	{
		minishell_input(&shell_data.token_root);
		print_tokens(shell_data.token_root);
		free_tokens(shell_data.token_root);
		shell_data.token_root = NULL;
	}
	return (0);
}
// system("leaks minishell");