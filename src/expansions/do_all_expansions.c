/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_all_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:18:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/08/01 13:19:28 by dgeorgiy         ###   ########.fr       */
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

// typedef struct s_exp
// {
// 	int		i;
// 	int		expanded_strlen;
// 	char	*expanded_str;
// 	char	*temp;
// }	t_exp;

// the free exp and init exp will go in expansion utils.

void	free_exp(t_exp *exp)
{
	free(exp->str);
	exp->exp_str = NULL;
	free(exp->temp);
	exp->temp = NULL;
	free(exp->exp_str);
	exp->exp_str = NULL;
}

int	init_exp(t_exp *exp, char *value)
{
	exp->strlen = 1;
	exp->i = 0;
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->exp_start = NULL;
	exp->exp_end = NULL;
	exp->str = ft_calloc(exp->strlen, sizeof(char));
	if (!(exp->str))
		return (-42);
	return (0);
}

//////

int	add_one_char_to_string(t_exp *exp, char c, t_token **head)
{
	exp->temp = exp->str;
	exp->str = ft_calloc(exp->strlen + 2, sizeof(char));
	if (!(exp->str))
		return (free_exp(&exp), free_tok_chain(head, del_tok_cont), -42);
	exp->str = ft_memcpy(exp->str, exp->temp, exp->strlen);
	(exp->str)[exp->strlen] = c;
	free(exp->temp);
	exp->temp = NULL;
	(exp->strlen)++;
	(exp->i)++;
	return (0);
}

int	expand_single_quotes(t_exp *exp, char *quotes_start, t_token **head)
{
	exp->exp_start = quotes_start;
	exp->exp_end = ft_strchr(exp->exp_start, '\'');
	exp->exp_strlen = exp->exp_end - exp->exp_start;
	exp->exp_str = ft_calloc(exp->exp_strlen + 1, sizeof(char));
	if (!(exp->exp_str))
		return (free_exp(&exp), free_tok_chain(head, del_tok_cont), -42);
	exp->exp_str = ft_memcpy(exp->exp_str, exp->exp_start, exp->exp_strlen);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->exp_str))
		return (free_exp(&exp), free_tok_chain(head, del_tok_cont), -42);
	free(exp->temp);
	free(exp->exp_str);
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->exp_strlen;
	(exp->i) += exp->exp_strlen + 2;
	return (0);
}

int	find_exp_var(t_exp *exp, char **envp)
{
	char	*var;
	char	*exp_var;

	if (exp->varlen == 0)
	{
		exp->exp_str = NULL;
		return (0);
	}
	var = ft_calloc(exp->varlen + 1, sizeof(char));
	if (!var)
		return (-42);
	var = ft_memcpy(var, exp->exp_start, exp->varlen);
	exp_var = find_var_in_envp(envp, var);
	free(var);
	if (!exp_var)
		exp->exp_str = NULL;
	else
	{
		exp->exp_str = ft_strdup(exp_var);
		if (!exp->exp_str)
			return (-42);	
	}
	return (0);
}

int	find_varlen(const char *str)
{
	int	varlen;

	varlen = 0;
	if (str[varlen] == '?' || str[varlen] == '$')
		return (varlen + 1);
	else
	{
		while (ft_isalnum(str[varlen]) || str[varlen] != '_')
			varlen++;
	}
	return (varlen);
}

int	expand_variable(t_exp *exp, char **envp, t_token **head)
{
	exp->varlen = find_varlen(exp->exp_start);
	if (find_exp_var(exp, envp) < 0)
		return (free_exp(&exp), free_tok_chain(head, del_tok_cont), -42);
	if (!exp->exp_str)
	{
		exp->exp_str = ft_calloc("", 1);
		if (!exp->exp_str)
			return (free_exp(&exp), free_tok_chain(head, del_tok_cont), -42);
	}
	exp->exp_strlen = ft_strlen(exp->exp_str);
	exp->temp = exp->str;
	exp->str = ft_strjoin(exp->temp, exp->exp_str);
	if (!(exp->str))
		return (free_exp(&exp), free_tok_chain(head, del_tok_cont), -42);
	free(exp->temp);
	free(exp->exp_str);
	exp->temp = NULL;
	exp->exp_str = NULL;
	exp->strlen += exp->exp_strlen;
	(exp->i) += exp->varlen + 1;
	return (0);
}

t_token	*expand_word(char *value, t_cshell *cshell)
{
	t_token	*head;
	t_exp	exp;

	if (init_exp(&exp, value) == -42);
		return (NULL);
	while (value[exp.i])
	{
		if (value[exp.i] == '$')
		{
			exp.exp_start = &(value[exp.i + 1]);
			if (expand_variable(&exp, cshell->envp, &head) < 0)
				return (NULL);
		}
		else if (value[exp.i] == '"')
		{
			// enter double quotes expansion
		}
		else if (value[exp.i] == '\'')
		{
			if (expand_single_quotes(&exp, &(value[exp.i + 1]), &head) < 0)
				return (NULL);
		}
		else
		{
			if (add_one_char_to_string(&exp, value[exp.i], &head) < 0)
				return (NULL);			
		}
	}
	return (head);
}

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