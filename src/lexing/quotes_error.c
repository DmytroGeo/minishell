/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 16:28:39 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 16:29:06 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.c"

void	quotes_error(int num_squotes, int num_dquotes, t_cshell *cshell)
{
	if (num_squotes % 2 == 1)
	{
		ft_printf(2, "minishell: syntax error: unclosed single quotes\n");
		cshell->exec_code = 2;
		(free_whole_shell(cshell), exit(cshell->exec_code));
	}
	if (num_dquotes % 2 == 1)
	{
		ft_printf(2, "minishell: syntax error: unclosed double quotes\n");
		cshell->exec_code = 2;
		(free_whole_shell(cshell), exit(cshell->exec_code));
	}
	return ;
}

void	wrong_number_of_quotes(t_cshell *cshell)
{
	int		num_squotes;
	int		num_dquotes;
	char	*curr;

	num_squotes = 0;
	num_dquotes = 0;
	curr = cshell->line_read;
	while (*curr)
	{
		if (*curr == '\'')
			num_squotes++;
		else if (*curr == '"')
			num_dquotes++;
		curr++;
	}
	quotes_error(num_squotes, num_dquotes, cshell);
	return ;
}