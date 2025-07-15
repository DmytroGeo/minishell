/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgeorgiy <dgeorgiy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 10:18:04 by dgeorgiy          #+#    #+#             */
/*   Updated: 2025/07/15 13:29:24 by dgeorgiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void do_all_expansions(t_token **tok_chain, int exit_status, char **envp)
// {
// 	t_token *current_token;
// 	(void)exit_status;
// 	(void)envp;
// 	current_token = *tok_chain;
// 	while (!is_EOF(current_token))
// 	{
// 		if (is_variable(current_token))
// 		{
// 			expand_variable(exit_status, envp, &current_token);
// 			ft_printf(1, "There's a variable\n");
// 		}
// 		else if (is_single_quotes(current_token))
// 			ft_printf(1, "There's a single-quoted string\n");
// 		else if (is_double_quotes(current_token))
// 		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ export a="ho 123"
// 		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ ec$a " $a "' $a '
// 		// 123  ho 123  $a 
// 		// dgeorgiy@c1r4s5:~/42_cursus_personal/minishell$ ec$a " $a " ' $a '
// 		// 123  ho 123   $a
// 			ft_printf(1, "There's a double-quoted string\n");	
// 		current_token = current_token->next;
// 	}
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