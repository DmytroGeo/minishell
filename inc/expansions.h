/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:12:25 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/04 16:42:42 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "structures.h"

int     expand_double_quotes(t_exp *exp, t_cshell *cshell);
int     expand_single_quotes(t_exp *exp);
int     expand_code(t_exp *exp, t_cshell *cshell);
int     init_exp(t_exp *exp, char *value);
int     add_one_char_to_string(t_exp *exp, char c);
int     check_and_expand_var(t_exp *exp, t_cshell *cshell);
int		add_one_char_to_exp(t_exp *exp, char c);
int		split_word(t_token **head, t_exp *exp);
int		find_exp_var(t_exp *exp, char **envp);

void	do_all_expansions(t_cshell *cshell);
void	free_exp(t_exp *exp);

char	*ft_dollar_strchr(const char *s);

#endif