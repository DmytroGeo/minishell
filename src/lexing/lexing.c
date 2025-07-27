/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/27 16:15:04 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexing.h"
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

void	init_lex(t_lex	*lex)
{
	lex->i = 0;
	lex->start = -1;
	lex->in_quotes = 0;
	lex->current_quote = 0;
	lex->next_raw_tok = NULL;
	return ;
}

void	init_raw_tok(t_lex *lex)
{
	free(lex->next_raw_tok);
	lex->next_raw_tok = NULL;
	return ;
}

void	lexing(t_cshell *cshell, char *line)
{
	t_lex		lex;
	t_op		operators[6];
	t_token		*new_token;
	t_tok_cont	*new_cont;

	populate_operators(operators);
	init_lex(&lex);
	if (find_next_raw_tok(line, &lex) == -42)
		(free_whole_cshell(cshell), exit(-42));
	while (lex.next_raw_tok)
	{
		new_cont = init_tok_cont(lex.next_raw_tok, operators);
		init_raw_tok(&lex);
		if (!new_cont)
			free_whole_cshell(cshell);
		new_token = ft_dlstnew(new_cont);
		if (!new_token)
			(del_tok_cont((void *)new_cont),
				free_whole_cshell(cshell), exit(-42));
		ft_dlstadd_back(&(cshell->token_chain), new_token);
		if (lex.i == (int)(ft_strlen(line)))
			return ;
		if (find_next_raw_tok(line, &lex) == -42)
			(free_whole_cshell(cshell), exit(-42));
	}
}
