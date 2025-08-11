/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:12:25 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/11 11:49:05 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H

# include "structures.h"

int		expand_double_quotes(t_exp *exp, t_cshell *cshell);
int		expand_single_quotes(t_exp *exp);
int		expand_code(t_exp *exp, t_cshell *cshell);
int		add_one_char_to_string(t_exp *exp, char c);
int		check_and_expand_var(t_exp *exp, t_cshell *cshell);
int		split_word(t_token **head, t_exp *exp);
int		find_exp_var(t_exp *exp, char **envp);
int		identify_expand(t_cshell *cshell, t_exp *exp, t_token **head);
int		add_last_bit_to_list(t_token **head, t_exp *exp);
int		find_varlen(const char *str);
int		expand_var_in_dquotes(t_exp *exp, t_cshell *cshell);
int		is_special_char(char c);

void	move_forward_by_n(t_exp *exp, int n);
void	do_all_expansions(t_cshell *cshell);
void	free_exp(t_exp *exp);
void	init_exp(t_exp *exp, char *value);

char	*ft_dollar_strchr(const char *s);

t_token	*duplicate_current_token(t_token *cur_tok);

#endif