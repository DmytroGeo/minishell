/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:12:25 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/30 11:09:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "structures.h"

char	*single_quotes_expansion(char *line);
char	*double_quotes_expansion(char *line, t_cshell *cshell);

void	do_all_expansions(t_cshell *cshell);

int		is_empty_line(const char *str);
int		is_valid_exp(const char *str);
int		find_varlen(const char *str);

#endif