/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baguiar- <baguiar-@student.42wolfsburg.de  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 00:51:43 by baguiar-          #+#    #+#             */
/*   Updated: 2024/11/29 00:51:48 by baguiar-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	setup_signals(void)
{
	signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, quit_signal);
}

void	reset_signals(void (*past_signal[2])(int))
{
	signal_setter(past_signal);
	signal_restore(past_signal);
}

void	setup_child_signals(void)
{
	signal(SIGINT, interrupt_signal);
	signal(SIGQUIT, quit_signal);
}
