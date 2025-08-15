/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:13:44 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/15 11:14:52 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_hd_exp(t_hd_exp *hd_exp, char *value)
{
	hd_exp->i = 0;
	hd_exp->varlen = 0;
	hd_exp->exp_varlen = 0;
	hd_exp->strlen = 0;
	hd_exp->non_var_len = 0;
	hd_exp->str = NULL;
	hd_exp->var = NULL;
	hd_exp->exp_var = NULL;
	hd_exp->temp = NULL;
	hd_exp->non_var_str = NULL;
	hd_exp->og_string = value;
	hd_exp->current = value;
}

void	free_hd_exp(t_hd_exp *hd_exp)
{
	hd_exp->i = 0;
	hd_exp->varlen = 0;
	hd_exp->exp_varlen = 0;
	hd_exp->strlen = 0;
	hd_exp->non_var_len = 0;
	free(hd_exp->str);
	hd_exp->str = NULL;
	free(hd_exp->non_var_str);
	hd_exp->non_var_str = NULL;
	free(hd_exp->temp);
	hd_exp->temp = NULL;
	free(hd_exp->exp_var);
	hd_exp->exp_var = NULL;
}
