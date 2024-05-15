/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/15 22:47:11 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void set_sighandler(struct sigaction *sa, void (*handler)(int))
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

t_data	init_env(int argc, char **argv, char **env)
{
	t_data	shell_data;

	(void)argc;
	(void)argv;
	if (access("/tmp", F_OK) == -1)
		perror_and_return("access /tmp", 0);
	g_signal = 0;
	ft_memset(&shell_data, 0, sizeof(t_data));
	set_sighandler(&shell_data.sa, handle_sigint);
	shell_data.var_lst = convert_env_to_linked_list(env);
	return (shell_data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	shell_data;

	shell_data = init_env(argc, argv, env);
	if (!shell_data.var_lst)
		perror_and_return("Failed to initialize minishell", 0);
	// print_env_var(shell_data.var_lst);
	while (1)
	{
		set_sighandler(&shell_data.sa, handle_sigint);
		minishell_input(&shell_data.token_root);
		print_tokens(shell_data.token_root);
		free_tokens(shell_data.token_root);
		shell_data.token_root = NULL;
	}
	return (0);
}
// system("leaks minishell");