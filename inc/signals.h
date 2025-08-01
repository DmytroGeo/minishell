/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:22:42 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 20:54:21 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "structures.h"

void	handle_sigint(int sig);
void	handle_child_sigint(int sig);
void	handle_child_sigquit(int sig);
void	init_signals(void);

#endif