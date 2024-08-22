/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:11:50 by sting             #+#    #+#             */
/*   Updated: 2024/08/22 11:20:48 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Enable echo of control characters
void	reset_terminal(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
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
	delete_var_from_var_lst("OLDPWD", &shell_data.var_lst);
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
		set_sighandler(&shell_data, handle_signal);
		status = minishell_input(&shell_data);
		if (status == 0)
			continue ;
		else if (status == -1)
			break ;
		set_sighandler(&shell_data, handle_signal_execute);
		shell_data.ast_root = create_ast(&shell_data);
		execute_ast(shell_data.ast_root);
		shell_data.token_root = NULL;
		free_ast(shell_data.ast_root);
		set_signal_exit_code(&shell_data);
	}
	free_var_lst(shell_data.var_lst);
	reset_terminal();
	return (0);
}

// free_tokens(shell_data.token_root);

// int	main(int argc, char **argv, char **env)
// {
// 	test(argc, argv, env);
//     #if defined(__linux__)
// 		system("valgrind --leak-check=full --show-leak-kinds=all ./minishell");
//     #elif defined(__APPLE__) && defined(__MACH__)
// 		system("leaks minishell");
// 	#endif
// 	return (0);
// }