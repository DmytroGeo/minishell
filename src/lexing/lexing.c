/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:59:28 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/24 12:51:17 by dgeorgiy         ###   ########.fr       */
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

void	lexing(t_cshell *cshell, char *line)
{
	char		**raw_tokens;
	t_op		operators[6];
	t_token		*new_token;
	t_tok_cont	*new_content;

	populate_operators(operators);
	raw_tokens = split_line(line);
	while (*raw_tokens)
	{
		new_content = init_tok_cont(*raw_tokens, operators);
		if (!new_content)
			return (free_whole_cshell(cshell), exit(1));
		new_token = ft_dlstnew(new_content);
		if (!new_token)
		{
			del_tok_cont((void *)new_content);
			return (free_whole_cshell(cshell), exit(1));
		}
		ft_dlstadd_back(&(cshell->token_chain), new_token);
		raw_tokens++;
	}
	return ;
}
