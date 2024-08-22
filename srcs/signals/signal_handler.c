/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zyeoh <zyeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 11:11:51 by zyeoh             #+#    #+#             */
/*   Updated: 2024/08/22 13:02:17 by zyeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

int	event(void)
{
	return (EXIT_SUCCESS);
}

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		rl_redisplay();
		rl_done = 1;
	}
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		rl_redisplay();
	}
}

void	handle_signal_execute(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = SIGINT;
		ft_printf("^C\n");
		rl_redisplay();
		rl_done = 1;
	}
	if (sig == SIGQUIT)
	{
		g_signal = SIGQUIT;
		ft_printf("^\\Quit: 3\n");
		rl_redisplay();
		rl_done = 1;
	}
}

void	set_signal_exit_code(t_data *shell_data)
{
	if (g_signal == SIGINT)
		set_exit_status(130, shell_data->var_lst);
	if (g_signal == SIGQUIT)
		set_exit_status(131, shell_data->var_lst);
	g_signal = 0;
}

void	set_sighandler(t_data *shell_data, void (*handler)(int))
{
	if (g_signal == SIGINT)
		set_exit_status(1, shell_data->var_lst);
	g_signal = 0;
	shell_data->sa.sa_handler = handler;
	sigemptyset(&shell_data->sa.sa_mask);
	shell_data->sa.sa_flags = 0;
	sigaction(SIGINT, &shell_data->sa, NULL);
	sigaction(SIGQUIT, &shell_data->sa, NULL);
}
