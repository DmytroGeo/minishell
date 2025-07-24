/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 18:12:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	populate_operators(t_op *operators)
{
	operators[0] = (t_op){"|", _pipe};
	operators[1] = (t_op){">", redir_out};
	operators[2] = (t_op){"<", redir_in};
	operators[3] = (t_op){">>", append};
	operators[4] = (t_op){"<<", heredoc};
	operators[5] = (t_op){NULL, word};
}

void	free_stuff(t_cshell *cshell, char **raw_tokens)
{
	ft_array_free((void **)raw_tokens);
	free_whole_cshell(cshell);
	exit(-42);
}

void	lexing(t_cshell *cshell, char *line)
{
	char		**raw_tokens;
	char		**curr_tok;
	t_op		operators[6];
	t_token		*new_token;
	t_tok_cont	*new_cont;

	populate_operators(operators);
	raw_tokens = split_line(line);
	curr_tok = raw_tokens;
	while (*curr_tok)
	{
		new_cont = init_tok_cont(*curr_tok, operators);
		if (!new_cont)
			free_stuff(cshell, raw_tokens);
		new_token = ft_dlstnew(new_cont);
		if (!new_token)
			(del_tok_cont((void *)new_cont), free_stuff(cshell, raw_tokens));
		ft_dlstadd_back(&(cshell->token_chain), new_token);
		curr_tok++;
	}
	ft_array_free((void **)raw_tokens);
	return ;
}
