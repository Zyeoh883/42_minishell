/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_w_readline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/16 16:28:43 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		rl_replace_line("", 0);
		// rl_redisplay();
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
		// exit(0);
	}
}

void	set_sighandler(struct sigaction *sa, void (*handler)(int))
{
	sa->sa_handler = handler;
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = 0;
	sigaction(SIGINT, sa, NULL);
}

void	setup_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term); // Get current terminal attributes
	term.c_lflag &= ~ECHOCTL;
	// Disable echo of control characters
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Set modified terminal attributes
}

void	reset_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term); // Get current terminal attributes
	term.c_lflag |= ECHOCTL;
	// Enable echo of control characters
	tcsetattr(STDIN_FILENO, TCSANOW, &term); // Set modified terminal attributes
}

t_data	init_env(int argc, char **argv, char **env)
{
	t_data	shell_data;

	(void)argc;
	(void)argv;
	if (access("/tmp", F_OK) == -1)
		perror_and_exit("access /tmp", 1);
	g_signal = 0;
	ft_memset(&shell_data, 0, sizeof(t_data));
	set_sighandler(&shell_data.sa, handle_sigint);
	shell_data.var_lst = convert_env_to_linked_list(env);
	setup_terminal();
	return (shell_data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	shell_data;

	shell_data = init_env(argc, argv, env);
	// print_env_var(shell_data.var_lst);
	while (1)
	{
		set_sighandler(&shell_data.sa, handle_sigint);
		if (minishell_input(&shell_data.token_root) > 0)
		{
			print_tokens(shell_data.token_root);
			free_tokens(shell_data.token_root);
			shell_data.token_root = NULL;
		}
		else
			break ;
	}
	reset_terminal();
	return (0);
}
// system("leaks minishell");