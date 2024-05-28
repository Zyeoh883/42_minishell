/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/05/28 17:44:38 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		rl_on_new_line();
		rl_replace_line("", 0);
		// printf("\n");
		rl_redisplay();
		rl_done = 1;
		// rl_event_hook = NULL;
	}
}

void	set_sighandler(struct sigaction *sa, void (*handler)(int))
{
	g_signal = 0;
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
	// term.c_cc[VMIN] = 0;
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
	shell_data.var_lst = convert_env_to_linked_list(env);
	setup_terminal();
	rl_event_hook = event;
	return (shell_data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	shell_data;
	int status;

	shell_data = init_env(argc, argv, env);
	while (1)
	{
		// rl_event_hook = event;
		set_sighandler(&shell_data.sa, handle_sigint);
		status = minishell_input(&shell_data.token_root);
		if (status == 0)
			continue ;
		else if (status == -1)
			break ;
		shell_data.ast_root = create_ast(&shell_data);
		print_ast(shell_data.ast_root, 0);
		// print_tokens(shell_data.token_root);
		// free_tokens(shell_data.token_root);
		shell_data.token_root = NULL;
	}
	// free_tokens(shell_data.token_root);
	reset_terminal();
	return (0);
}

// int	test(int argc, char **argv, char **env)
// {
// 	t_data	shell_data;

// 	shell_data = init_env(argc, argv, env);
// 	// print_env_var(shell_data.var_lst);
// 	while (1)
// 	{
// 		set_sighandler(&shell_data.sa, handle_sigint);
// 		if (minishell_input(&shell_data.token_root) > 0)
// 			print_tokens(shell_data.token_root);
// 		else
// 			break ;
// 		free_tokens(shell_data.token_root);
// 		shell_data.token_root = NULL;
// 	}
// 	free_tokens(shell_data.token_root);
// 	reset_terminal();
// 	return (0);
// }
// system("leaks minishell");

// int main(void)
// {
// 	struct sigaction sa;
// 	char *input;

// 	set_sighandler(&sa, handle_sigint);
// 	input = NULL;
// 	input = readline("input$ ");
// 	printf("input = %p\n", input);
// 	if (input)
// 		printf("input = %s\n", input);
// 	return (0);
// }

