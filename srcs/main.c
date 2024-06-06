/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/06/06 16:46:40 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

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

void	set_sighandler(t_data *shell_data, void (*handler)(int))
{
	char	*temp;

	if (g_signal == SIGINT)
	{
		temp = get_var_value("?=", shell_data->var_lst);
		// printf("%s\n", temp);
		if (ft_atoi(temp) != 130)
			set_exit_status(1, shell_data->var_lst);
	}
	g_signal = 0;
	shell_data->sa.sa_handler = handler;
	sigemptyset(&shell_data->sa.sa_mask);
	shell_data->sa.sa_flags = 0;
	sigaction(SIGINT, &shell_data->sa, NULL);
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

// rl_event_hook = event;
int	main(int argc, char **argv, char **env)
{
	t_data	shell_data;
	int		status;

	shell_data = init_env(argc, argv, env);
	while (1)
	{
		set_sighandler(&shell_data, handle_sigint);
		status = minishell_input(&shell_data);
		if (status == 0)
			continue ;
		else if (status == -1)
			break ;
		print_tokens(shell_data.token_root);
		shell_data.ast_root = create_ast(&shell_data);
		
		print_ast(shell_data.ast_root, 0);
		print_ast(shell_data.ast_root, 0);
		printf("main: redir filename: %s\n", (*shell_data.ast_root->simple_command->redir)->filename); // ! remove later
		
		// execute_ast(shell_data.ast_root);
		// print_tokens(shell_data.token_root);
		// free_tokens(shell_data.token_root);

		shell_data.token_root = NULL;
	}
	reset_terminal();
	return (0);
}
// free_tokens(shell_data.token_root);

// int main(void)
// {
// 	test();
// 	system("leaks minishell");
// 	return (0);
// }
