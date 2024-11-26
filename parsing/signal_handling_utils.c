
#include "../lib/minishell.h"

void setup_signals(void)
{
	signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, SIG_IGN);
}

void reset_signals(void (*past_signal[2])(int))
{
		signal_setter(past_signal);
		signal_restore(past_signal);
}
