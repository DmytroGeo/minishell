/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:18:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/31 12:03:20 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "minishell.h"
#include "lexing.h"

// to get the pid
// look into proc/self/stat


// idea:
// let's say we have $a" my" where $a="hello there"
// if coming across an unquoted var ($a in our case)
// we expand it so now we have ""
// t_token	*expand_word(char *value, t_cshell *cshell)
// {
// 	t_token	*head;
// 	int i;

// 	i = 0;
// 	while (value[i])
// 	{
// 		if (value[i] == '$')
// 		{
// 			exp->varlen = find_varlen(exp->cur + 1);
// 			if (exp->varlen == 1 && *(exp->cur + 1) == '?')
// 				exp->expanded_var = ft_itoa(exec_code);
// 			else if (exp->varlen == 1 && *(exp->cur + 1) == '$')
// 				exp->expanded_var = ft_itoa(cshell->shell_id);
// 			else
// 			{
// 				var = find_var(exp->cur + 1, exp->varlen);
// 				if (!var)
// 					(free_exp(exp), free_whole_cshell(cshell), exit(-42));
// 				exp->expanded_var = ft_strdup(find_var_in_envp(cshell->envp, var));
// 				free(var);			
// 			}
// 		}
// 		else if (value[i] == '"')
// 		{
			
// 		}
// 		else if (value[i] == '\'')
// 		{
			
// 		}
// 		i++;
// 	}
// 	return (head);
// }

t_token	*duplicate_current_token(t_token *cur_tok)
{
	t_tok_cont	*content;
	t_token		*new_token;

	content = malloc(sizeof(t_tok_cont));
	if (!content)
		return (NULL);
	content->value = ft_strdup(((t_tok_cont *)(cur_tok->content))->value);
	content->type = ((t_tok_cont *)(cur_tok->content))->type;
	new_token = ft_dlstnew(content);
	if (!new_token)
		return (del_tok_cont((void *)content), NULL);
	return (new_token);
}

t_token	*split_node(t_token	*cur_tok, t_cshell *cshell)
{
	char		*value;
	t_tok_type	type;
	t_token		*new_tok_chain;
	
	new_tok_chain = NULL;
	type = ((t_tok_cont *)(cur_tok->content))->type;
	if (type != word)
		new_tok_chain = duplicate_current_token(cur_tok);
	else
	{
		value = ((t_tok_cont *)(cur_tok->content))->value;
		new_tok_chain = expand_word(value, cshell);
	}
	return (new_tok_chain);
}

void	do_all_expansions(t_cshell *cshell)
{
	t_token	*cur_tok;
	t_token	*split_token;
	t_token	*new_head;

	cur_tok = cshell->token_chain;
	while (cur_tok->next)
	{
		split_token = split_node(cur_tok, cshell);
		if (!split_token)
		{
			free_tok_chain(&new_head, del_tok_cont);
			(free_whole_cshell(cshell), exit(-42));
		}
		ft_dlstadd_back(&new_head, split_token);
		cur_tok = cur_tok->next;	
	}
	free_tok_chain(&(cshell->token_chain), del_tok_cont);
	cshell->token_chain = new_head;
	return ;
}

// }

		///////////////////////
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ <<
		// bash: syntax error near unexpected token `newline'
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat <<hello
		// > hii
		// > $USER
		// > hello
		// hii
		// dgeorgiy
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << 'hello'
		// > hiiui
		// > $USER
		// > 'hello'
		// > hello
		// hiiui
		// $USER
		// 'hello'
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << "hello"
		// > hii
		// > $USER
		// > hello
		// hii
		// $USER
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ cat << hel"l"o
		// > hi
		// > $USER
		// > hel"l"o
		// > hello
		// hi
		// $USER
		// hel"l"o
		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$
		///////////////////////////