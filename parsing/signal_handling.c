

#include "../lib/minishell.h"

int	g_signal = 0;

//handle ctrl+c
void	interrupt_signal(int signal)
{
	signal = 130;
	g_signal = signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Handle ctrl+'\' to quit
void	quit_signal(int signal)
{
	signal = 131;
	g_signal = signal;
	printf("Quit (core dumped)\n");
}

void	signal_setter(void (**past_signal)(int))  // Note: passing pointer to pointer
{
	past_signal[0] = signal(SIGINT, interrupt_signal);  // Set SIGINT handler
	past_signal[1] = signal(SIGQUIT, quit_signal);  // Set SIGQUIT handler
}

void	signal_restore(void (**past_signal)(int))  // Note: passing pointer to pointer
{
	signal(SIGINT, past_signal[0]);  // Restore previous SIGINT handler
	signal(SIGQUIT, past_signal[1]);  // Restore previous SIGQUIT handler
}
