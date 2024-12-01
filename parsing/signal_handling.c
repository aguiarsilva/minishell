/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:57:10 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/29 00:57:16 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	g_signal = 0;

void	sig_int(int signal)
{
	(void)signal;
	g_signal = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_int_in_process(int signal)
{
	signal = 130;
	g_signal = signal;
	printf("\n");
}

void	sig_quit(int signal)
{
	(void)signal;
	if (rl_line_buffer && *rl_line_buffer)
	{
		g_signal = 131;
		printf("Quit\n");
		rl_on_new_line();
		rl_redisplay();
	}
	return ;
}

void	set_signals(void (*old_signal[2])(int))
{
	old_signal[0] = signal(SIGINT, sig_int);
	old_signal[1] = signal(SIGQUIT, SIG_IGN);
}

void	restore_signals(void (*old_signal[2])(int))
{
	signal(SIGINT, old_signal[0]);
	signal(SIGQUIT, old_signal[1]);
}

// void	interrupt_signal(int signal)
// {
// 	signal = 130;
// 	g_signal = signal;
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	quit_signal(int signal)
// {
// 	signal = 131;
// 	g_signal = signal;
// 	printf("Quit (core dumped)\n");
// }

// void	signal_setter(void (**past_signal)(int))
// {
// 	past_signal[0] = signal(SIGINT, interrupt_signal);
// 	past_signal[1] = signal(SIGQUIT, quit_signal);
// }

// void	signal_restore(void (**past_signal)(int))
// {
// 	signal(SIGINT, past_signal[0]);
// 	signal(SIGQUIT, past_signal[1]);
// }
