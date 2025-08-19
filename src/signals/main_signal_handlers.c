/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal_handlers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:22:08 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/19 11:49:03 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include "minishell.h"

extern volatile sig_atomic_t	g_received_signal;

// void	handle_sigint(int sig)
// {
// 	(void)sig;
// 	write(STDOUT_FILENO, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// 	g_received_signal = sig;
// }

// void	init_signals(void)
// {
// 	signal(SIGINT, handle_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }

void    handle_sigint(int sig)
{
    (void)sig;
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_received_signal = sig;
}
void handle_hd_sigint(int sig)
{
    (void)sig;
    g_received_signal = sig;
}

void    set_heredoc_signals(void)
{
    struct sigaction    sa;
    ft_bzero(&sa, sizeof(sa));
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handle_hd_sigint;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}

void    restore_main_signals(void)
{
    init_signals();
    // struct sigaction sa;
    // ft_bzero(&sa, sizeof(sa));
    // sigemptyset(&sa.sa_mask);
    // sa.sa_handler = handle_sigint;
    // sa.sa_flags = 0;
    // sigaction(SIGINT, &sa, NULL);
    // signal(SIGQUIT, SIG_IGN);
}

void    init_signals(void)
{
    rl_catch_signals = 0;
    rl_catch_sigwinch = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}
