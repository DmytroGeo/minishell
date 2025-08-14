/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:12:25 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/14 19:23:15 by dgeorgiy         ###   ########.fr       */
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
int		add_last_str_stuff_to_list(t_token **head, t_exp *exp);
int		find_varlen(const char *str);
int		expand_var_in_dquotes(t_exp *exp, t_cshell *cshell);
int		is_special_char(char c);

void	get_in_string_cont(t_qts_remov *qts_remov);
void	move_forward_by_n(t_exp *exp, int n);
void	do_all_expansions(t_cshell *cshell);
void	free_exp(t_exp *exp);
void	init_exp(t_exp *exp, char *value);
void	init_quotes_removal(t_qts_remov	*qts_remov, char *value);
void	free_quotes_removal(t_qts_remov *qts_remov);

char	*ft_dollar_strchr(const char *s);
char	*quotes_removal(char *value);
char	*find_first_space(t_exp *exp);
char	*find_next_quote(const char *s);

t_token	*duplicate_current_token(t_token *cur_tok);
t_token	*strip_quotes(char *value);

#endif