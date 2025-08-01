/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:12:25 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 20:17:43 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "structures.h"

int     expand_double_quotes(t_exp *exp, t_cshell *cshell, t_token **head);
int     expand_single_quotes(t_exp *exp, t_token **head);
int     expand_code(t_exp *exp, t_cshell *cshell, t_token **head);
int     init_exp(t_exp *exp, char *value);
int     add_one_char_to_string(t_exp *exp, char c, t_token **head);
int     check_and_expand_var(t_exp *exp, t_cshell *cshell, t_token **head);

void	do_all_expansions(t_cshell *cshell);
void	free_exp(t_exp *exp);
char	*ft_dquote_strchr(const char *s);

#endif