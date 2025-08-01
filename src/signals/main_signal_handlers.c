/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:22:08 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 21:41:26 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "signals.h"

sig_atomic_t g_received_signal = 0;

void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_received_signal = SIGINT;
}

void	handle_child_sigint(int sig)
{
	(void)sig;
	// write(1, "\n", 1);
	exit(130);
}

void	handle_child_sigquit(int sig)
{
	(void)sig;
	write(1, "Quit: 3\n", 8);
	exit(131);
}
/*
void    handle_sigquit(int sig)
{
    g_received_signal = SIGQUIT;
}
void    respond_to_signal(void)
{
    if (g_received_signal == SIGINT)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
    else if (g_received_signal == SIGQUIT)
    {
        write(2, "Quit: 3\n", 8);
    }
    g_received_signal = 0;
}
*/
void	init_signals(void)
{
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
