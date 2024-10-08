#include "../lib/minishell.h"

int	g_signal = 0;

//handle ctrl+c
void	interrupt_signal(int signal)
{
	signal = 130;
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line();
	rl_redisplay();
}

void	interruption_signal_process(int signal)
{
	signal = 130;
	g_signal = signal;
	printf("\n");
}

//handle ctrl+'\' to quit
void	quit_signal(int signal)
{
	signal = 131;
	g_signal = signal;
	printf("\n");
}

void	signal_setter(void (*past_signal[2])(int))
{
	past_signal[0] = signal(SIGINT, interruption_signal_process);
	past_signal[1] = signal(SIGQUIT, quit_signal);
}

void	signal_restore(void(*past_signal[2])(int))
{
	signal(SIGINT, past_signal[0]);
	signal(SIGQUIT, past_signal[1]);
}
